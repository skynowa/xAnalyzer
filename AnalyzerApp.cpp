/**
 * \file  AnalyzerApp.cpp
 * \brief AnalyzerApp
 */


#include "AnalyzerApp.h"

#include "Analyzers/IAnalyzer.h"
#include "AnalyzersFactory.h"


namespace xa
{
//-------------------------------------------------------------------------------------------------
AnalyzerApp::AnalyzerApp(
	std::ctstring_t &a_appGuid,
	std::ctstring_t &a_locale
) :
	Application(a_appGuid, a_locale)
{
	{
		std::vec_tstring_t appArgs;
		args(true, &appArgs);
		Cout() << xTRACE_VAR(appArgs);

		std::vector<CmdOptionsUsage> usage;

		CmdOptions options;
		options.parse(appArgs, usage);
	}

	// current OS
	_os_name = SystemInfo().os();

	// analyzer type
	_type = ::TypeActive::TYPE_ACTIVE;

	// analyzer name
	std::map<::TypeActive, std::tstring_t> names
	{
		{::TypeActive::TYPE_CPPCHECK,        "[Cppcheck]"},
		{::TypeActive::TYPE_CLANG_TIDY,      "[Clang-Tidy]"},
		{::TypeActive::TYPE_CLANG_TIDY_DIFF, "[Clang-Tidy-Diff]"},
		{::TypeActive::TYPE_CLANG_TIDY_FILE, "[Clang-Tidy-File]"}
	};

	_name = names[_type];
	if (_name == "") {
		traceError("Bad type: " + Enum::str(_type));
		Process::currentExit(1);
		return;
	}

	// GIT modified files
	_git.modifiedFiles(::CPP_MASK, &_git_modified_files);
	if (_git_modified_files.empty() &&
		_type != ::TypeActive::TYPE_CLANG_TIDY_FILE)
	{
		traceOk("No changes. OK");
		Process::currentExit(1);
		return;
	}

	// compiler info
	complierInfo(&_complier_id, &_complier_name);

	// C++ include dirs
	includeDirs(&_include_dirs);
}
//-------------------------------------------------------------------------------------------------
AnalyzerApp::ExitCode
AnalyzerApp::onRun() /* override */
{
	if (::QUICK_CHECK) {
		traceOk("Start analysis (quick)...");
	} else {
		traceOk("Start analysis (full)...");
	}

	// profiler
	/// time_start_sec = time.time();

	std::tstring_t stdOut;
	std::tstring_t stdError;
	{
		if (false) {
			const std::vector<AnalyzersFactory::Type> analyzerTypes
			{
				AnalyzersFactory::Type::CppCheck,
				AnalyzersFactory::Type::ClangTidy
			};

			for (const auto &it_analyzerType : analyzerTypes) {
				auto &analyzer = AnalyzersFactory::create(it_analyzerType);
				analyzer->run();

			}
		}
		else {
			switch (_type) {
			case ::TypeActive::TYPE_CPPCHECK:
				{
					auto &analyzer = AnalyzersFactory::create(AnalyzersFactory::Type::CppCheck);
					analyzer->run();
				}
				break;
			case ::TypeActive::TYPE_CLANG_TIDY:
				{
					auto &analyzer = AnalyzersFactory::create(AnalyzersFactory::Type::ClangTidy);
					analyzer->run();
				}
				break;
			case ::TypeActive::TYPE_CLANG_TIDY_DIFF:
				{
					auto &analyzer = AnalyzersFactory::create(AnalyzersFactory::Type::ClangTidy);
					/// self.runClangTidyDiff();
					analyzer->run();
				}
				break;
			case ::TypeActive::TYPE_CLANG_TIDY_FILE:
				{
					auto &analyzer = AnalyzersFactory::create(AnalyzersFactory::Type::ClangTidy);
					/// self.runClangTidyFile();
					analyzer->run();
				}
				break;
			}
		}

		// TODO: stdOut, stdError - fill

		stdOut   = ::String::trimSpace(stdOut);
		stdError = ::String::trimSpace(stdError);
	}

	// TODO: profiler
	std::ctstring_t time_stop_sec_str = "";
	/// time_stop_sec_str = "({0:.2f} sec)".format(time.time() - time_start_sec);

	trace(stdOut);

	// rm extra warning info
	/// stdOut   = re.sub("^\d+ warnings generated\.", "", stderr_str).strip(" \t\r\n");
	/// stdError = re.sub("^\d+ warnings generated\.", "", stderr_str).strip(" \t\r\n");

	/// stdError = re.sub("^\d+ warnings and \d error generated\.", "", stdError).strip(" \t\r\n");
	traceError(stdError);

	if ( isError(stdOut, stdError) ) {
		if (::STOP_ON_FAIL) {
			traceError("***** Detect errors. Commit stopped ***** " + time_stop_sec_str);

			return ExitCode::Failure;
		} else {
			traceError("***** Detect errors. Commited ***** " + time_stop_sec_str);
		}
	} else {
		traceOk("No warnings. OK " + time_stop_sec_str);
	}

	return ExitCode::Success;
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerApp::complierInfo(
	::CompilerId   *out_complier_id,
	std::tstring_t *out_complier_name
) const
{
	xCHECK_DO(out_complier_id == nullptr, return);
	xCHECK_DO(out_complier_name == nullptr, return);

	*out_complier_id   = {};
	*out_complier_name = {};

	std::cvec_tstring_t params
	{
		"--version"
	};

	std::tstring_t stdOut;
	std::tstring_t stdError;

	Process::execute("c++", params, {}, xTIMEOUT_INFINITE, &stdOut, &stdError);
#if 0
	if (out.returncode == 1):
		self.traceError("complierInfo")
		return self.COMPILER_ID_UNKNOWN
#endif

	std::ctstring_t &version_str = String::trimSpace(stdOut);
	if (version_str.find("clang version") != std::tstring_t::npos) {
		*out_complier_id   = ::CompilerId::COMPILER_ID_CLANG;
		*out_complier_name = "clang";
	} else {
		*out_complier_id   = ::CompilerId::COMPILER_ID_GCC;
		*out_complier_name = "gcc";
	}
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerApp::includeDirs(
	std::vec_tstring_t *out_dirPathes
) const
{
	xCHECK_DO(out_dirPathes == nullptr, return);

	out_dirPathes->clear();

	if (::TypeActive::TYPE_ACTIVE == ::TypeActive::TYPE_CPPCHECK &&
		::QUICK_CHECK)
	{
		*out_dirPathes = {};
	} else {
		// System includes (cpp -v)
		if (true) {
			std::vec_tstring_t dirPathes;
			compilerIncludeDirs(&dirPathes);

			*out_dirPathes = dirPathes;
		} else {
			*out_dirPathes =
				{
					"-I/usr/lib/gcc/x86_64-linux-gnu/8/include",
					"-I/usr/local/include",
					"-I/usr/lib/gcc/x86_64-linux-gnu/8/include-fixed",
					"-I/usr/include/x86_64-linux-gnu",
					"-I/usr/include"
				};
		}

		std::vec_tstring_t dirPathes
		{
			"-I/usr/local/include ",
			/// "".join(self.getPkgConfig("libxml-2.0")),
			/// "".join(self.getPkgConfig("ImageMagick")),

			"-I/usr/local/gen++v3/class",
			"-I" +       ::PROJECT_DIR + "/functions",
			"-isystem" + ::PROJECT_DIR + "/suppliers/gen/base",
			"-isystem" + ::PROJECT_DIR + "/booked/gen/base",
			"-isystem" + ::PROJECT_DIR + "/syntexts/gen/base",
			"-isystem" + ::PROJECT_DIR + "/core/gen/base",
			"-isystem" + ::PROJECT_DIR + "/api/gen/base",
			"-isystem" + ::PROJECT_DIR + "/seo/gen/base"
		};

		out_dirPathes->insert(out_dirPathes->end(), dirPathes.cbegin(), dirPathes.cend());
	}
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerApp::compilerIncludeDirs(
	std::vec_tstring_t *out_dirPathes
) const
{
	xCHECK_DO(out_dirPathes == nullptr, return);

	out_dirPathes->clear();

	std::cvec_tstring_t params
	{
		"-v",
		"/dev/null"
	};

	std::tstring_t stdOut;
	std::tstring_t stdError;

	Process::execute("clang-tidy", params, {}, xTIMEOUT_INFINITE, &stdOut, &stdError);

	std::tstring_t str_left  = "#include <...> search starts here:";
	std::tstring_t str_right = "End of search list.";

	std::csize_t pos_left  = stdOut.find(str_left);
	std::csize_t pos_right = stdOut.find(str_right, pos_left);
	xTEST_LESS(pos_left, pos_right);

	/// stdOut = stdOut[int(pos_left) + len(str_left):int(pos_right)].strip();

	std::vec_tstring_t includes;
	String::split(stdOut, "???", &includes);

	for (const auto &it_include : includes) {
		out_dirPathes->push_back("-I" + it_include);
	}

	if (_os_name == SystemInfo::OsType::FreeBSD) {
		out_dirPathes->push_back("-isystem/usr/include/c++/v1");
	}
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerApp::getPkgConfig(
	std::ctstring_t &a_lib_name
) const
{
#if 0
def getPkgConfig(self, a_lib_name):
	"" Get libs, cflags by pkg-config tool ""

	try:
		# cmd_libs = ["pkg-config", "--libs-only-L",   a_lib_name]
		# libs = (
		#     subprocess.check_output(cmd_libs)
		#     .decode("utf8")
		#     .strip()
		#     # .replace("-L", "")
		# )

		cmd_cflags = ["pkg-config", "--cflags-only-I", a_lib_name]
		cflags = (
			subprocess.check_output(cmd_cflags)
			.decode("utf8")
			.strip()
			.replace("-I", "-isystem") # suppress all warnings
		)

		return (cflags)
	except Exception:
		self.traceError("pkg-config: " + a_lib_name + " - fail")
		pass
#else

#endif
}
//-------------------------------------------------------------------------------------------------
bool_t
AnalyzerApp::isError(
	std::ctstring_t &a_out,
	std::ctstring_t &a_stderr_str
) const
{
#if 0
def isError(self, a_out, a_stderr_str):
	"" Check if errors detected ""

	return bool((a_out.returncode == 1 or re.search("^.*(error|warning).*$", a_stderr_str, re.MULTILINE)) and
		a_stderr_str.find("Error while processing") > 0)
#else
	return false;
#endif
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerApp::traceOptions() const
{
	trace("");
	traceOk("Options:");
	trace("TYPE_ACTIVE: " + _name);
	/// trace("COMPILER_ID: " + self._complier_name);
	trace("QUICK_CHECK: " + std::to_string(::QUICK_CHECK));
	trace("SKIP_CHECK:  " + std::to_string(::SKIP_CHECK));
	trace("STOP_ON_FAIL:" + std::to_string(::STOP_ON_FAIL));
	trace("CPP_STD:     " + ::CPP_STD);
	trace("CPP_MASK:    " + String::join(::CPP_MASK, ", "));
	trace("");
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerApp::traceColor(
	std::ctstring_t &a_color,
	std::ctstring_t &a_msg
) const
{
#if 0
def traceColor(self, a_color, a_msg):
	"" Trace using color ""

	if (len(a_msg) == 0):
		return

	print(a_color + self._name + self.COLOR_NORMAL + " " + a_msg)
#else
	trace(a_msg);
#endif
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerApp::trace(
	std::ctstring_t &a_msg
) const
{
	Cout() << a_msg;
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerApp::traceOk(
	std::ctstring_t &a_msg
) const
{
#if 0
def traceOk(self, a_msg):
	"" Trace as OK ""

	if (len(a_msg) == 0):
		return

	print(self.COLOR_YELLOW + self._name + self.COLOR_NORMAL + " " +
		self.COLOR_GREEN + a_msg + self.COLOR_NORMAL)
#else
	trace(a_msg);
#endif
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerApp::traceError(
	std::ctstring_t &a_msg
) const
{
#if 0
def traceError(self, a_msg):
	"" Trace as error ""

	if (len(a_msg) == 0):
		return

	print(self.COLOR_RED + self._name + " " + a_msg + self.COLOR_NORMAL)
#else
	trace(a_msg);
#endif
}
//-------------------------------------------------------------------------------------------------
} // namespace xa
