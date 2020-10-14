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
	_console.setEscapeValues(false);

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
	if ( _name.empty() ) {
		traceError("Bad type: " + Enum::str(_type));
		Process::currentExit(1);
		return;
	}

	// GIT modified files
	_git.modifiedFiles(::CPP_MASK, &_git_modified_files);

	// compiler info
	complierInfo(&_complier_id, &_complier_name);

	// C++ include dirs
	includeDirs(&_include_dirs);

	traceOptions();
}
//-------------------------------------------------------------------------------------------------
AnalyzerApp::ExitCode
AnalyzerApp::onRun() /* override */
{
	if (_git_modified_files.empty() &&
		_type != ::TypeActive::TYPE_CLANG_TIDY_FILE)
	{
		traceOk("No changes. OK");
		return ExitCode::Success;
	}

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
		}

		traceError("***** Detect errors. Commited ***** " + time_stop_sec_str);
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

	Process::execute("/usr/bin/c++", params, {}, xTIMEOUT_INFINITE, &stdOut, &stdError);
#if 0
	Cout() << xTRACE_VAR(stdOut);
	Cout() << xTRACE_VAR(stdError);
#endif

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

		// libxml
		{
			std::vec_tstring_t cflags;
			pkgConfig("libxml-2.0", &cflags);
			out_dirPathes->insert(out_dirPathes->end(), cflags.cbegin(), cflags.cend());
		}

		// ImageMagick
		{
			std::vec_tstring_t cflags;
			pkgConfig("ImageMagick", &cflags);
			out_dirPathes->insert(out_dirPathes->end(), cflags.cbegin(), cflags.cend());
		}

		std::vec_tstring_t dirPathes
		{
			"-I/usr/local/include ",

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

	// System includes (cpp -v)
	std::cvec_tstring_t params
	{
		"-v",
		"/dev/null"
	};

	std::tstring_t stdOut;
	std::tstring_t stdError;

	Process::execute("/usr/bin/cpp", params, {}, xTIMEOUT_INFINITE, &stdOut, &stdError);
	xUNUSED(stdOut);
#if 0
	Cout() << xTRACE_VAR(stdOut);
	Cout() << xTRACE_VAR(stdError);
#endif

	std::tstring_t str_left  = "#include <...> search starts here:";
	std::tstring_t str_right = "End of search list.";

	std::csize_t pos_left  = stdError.find(str_left);
	std::csize_t pos_right = stdError.find(str_right, pos_left);
	xTEST_LESS(pos_left, pos_right);

	stdError = String::trimSpace( String::cut(stdError, str_left, str_right) );

	std::vec_tstring_t includes;
	String::split(stdError, Const::nl(), &includes);

	for (const auto &it_include : includes) {
		out_dirPathes->push_back("-I" + String::trimSpace(it_include));
	}

	if (_os_name == SystemInfo::OsType::FreeBSD) {
		out_dirPathes->push_back("-isystem/usr/include/c++/v1");
	}
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerApp::pkgConfig(
	std::ctstring_t    &a_lib_name,
	std::vec_tstring_t *out_cflags
) const
{
	xTEST(!a_lib_name.empty());
	xTEST_PTR(out_cflags);

	out_cflags->clear();

	std::cvec_tstring_t params_cflags
	{
		"--cflags-only-I",
		a_lib_name
	};

	std::tstring_t stdOut;
	std::tstring_t stdError;

	Process::execute("/usr/bin/pkg-config", params_cflags, {}, xTIMEOUT_INFINITE, &stdOut, &stdError);
#if 0
	Cout() << xTRACE_VAR(stdOut);
	Cout() << xTRACE_VAR(stdError);
#endif

	// suppress all warnings
	stdOut = String::replaceAll(String::trimSpace(stdOut), "-I", "-isystem");

	String::split(stdOut, Const::nl(), out_cflags);
	if ( out_cflags->empty() ) {
		traceError("pkg-config: " + a_lib_name + " - fail");
		return;
	}
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

	return
		bool((a_out.returncode == 1 or
			  re.search("^.*(error|warning).*$", a_stderr_str, re.MULTILINE)) and
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
	trace("COMPILER_ID: " + _complier_name);
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
	Console::Foreground  a_color,
	std::ctstring_t     &a_msg
) const
{
	xCHECK_DO(a_msg.empty(), return);

	std::ctstring_t str = _console.setAttributesText(a_color, Console::Background::Default,
		static_cast<int_t>(Console::Attribute::Bold), _name);

	_console.writeLine(str + " " + a_msg);
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerApp::trace(
	std::ctstring_t &a_msg
) const
{
	_console.writeLine(a_msg);
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerApp::traceOk(
	std::ctstring_t &a_msg
) const
{
	xCHECK_DO(a_msg.empty(), return);

	std::tstring_t str;
	str = _console.setAttributesText(Console::Foreground::Yellow , Console::Background::Default,
		static_cast<int_t>(Console::Attribute::Bold), _name);
	str += _console.setAttributesText(Console::Foreground::Green , Console::Background::Default,
		static_cast<int_t>(Console::Attribute::Bold), " " + a_msg);

	_console.writeLine(str);
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerApp::traceError(
	std::ctstring_t &a_msg
) const
{
	xCHECK_DO(a_msg.empty(), return);

	std::ctstring_t str =
		_console.setAttributesText(Console::Foreground::Red , Console::Background::Default,
		static_cast<int_t>(Console::Attribute::Bold), _name + " " + a_msg);

	_console.writeLine(str);
}
//-------------------------------------------------------------------------------------------------
} // namespace xa
