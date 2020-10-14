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
#if 0
def __init__(self, a_type):
	"" Constructor ""

	"" Constants ""

	"" Project root directory ""
	self.PROJECT_DIR = "/home/httpd/triptake-all"

	"" Shell colors ""
	self.COLOR_RED     = "\033[0;91m"
	self.COLOR_YELLOW  = "\033[0;93m"
	self.COLOR_GREEN   = "\033[0;92m"
	self.COLOR_MAGENTA = "\033[0;95m"
	self.COLOR_NORMAL  = "\033[0m"

	"" Compiler types ""
	self.COMPILER_ID_UNKNOWN = 0
	self.COMPILER_ID_CLANG   = 1
	self.COMPILER_ID_GCC     = 2

	"" Number of jobs (Cppcheck support only) ""
	self.JOBS_NUM = str(multiprocessing.cpu_count())


	"" current OS ""
	self._os_name = os.uname()[0]

	"" analyzer type ""
	self._type = a_type

	"" analyzer name ""
	names = {
		options.TYPE_CPPCHECK:        "[Cppcheck]",
		options.TYPE_CLANG_TIDY:      "[Clang-Tidy]",
		options.TYPE_CLANG_TIDY_DIFF: "[Clang-Tidy-Diff]",
		options.TYPE_CLANG_TIDY_FILE: "[Clang-Tidy-File]"
	}

	self._name = names[a_type]
	if (self._name == ""):
		self.traceError("Bad type: " + a_type)
		sys.exit(1)

	"" GIT modified files ""
	self._git_modified_files = self.getGitModifiedFiles()
	if (len(self._git_modified_files) == 0 and self._type != options.TYPE_CLANG_TIDY_FILE):
		self.traceOk("No changes. OK")
		sys.exit(0)

	"" compiler info ""
	self._complier_id, self._complier_name = self.getComplierInfo()

	"" C++ include dirs ""
	self._include_dirs = self.getIncludeDirs()

	"" file to check for manual run ""
	self._file_to_check = ""
#else
	std::vec_tstring_t appArgs;
	args(true, &appArgs);
	Cout() << xTRACE_VAR(appArgs);

	std::vector<CmdOptionsUsage> usage;

	CmdOptions options;
	options.parse(appArgs, usage);
#endif
}
//-------------------------------------------------------------------------------------------------
AnalyzerApp::ExitCode
AnalyzerApp::onRun() /* override */
{
#if 0
def run(self):
	"" Run analysis by type ""

	if (options.QUICK_CHECK == 1):
		self.traceOk("Start analysis (quick)...")
	else:
		self.traceOk("Start analysis (full)...")

	out = None

	# profiler
	time_start_sec = time.time()

	if   (self._type == options.TYPE_CPPCHECK):
		out = self.runCppcheck()
	elif (self._type == options.TYPE_CLANG_TIDY):
		out = self.runClangTidy()
	elif (self._type == options.TYPE_CLANG_TIDY_DIFF):
		out = self.runClangTidyDiff()
	elif (self._type == options.TYPE_CLANG_TIDY_FILE):
		out = self.runClangTidyFile()

	stdout,stderr = out.communicate()
	stdout_str = stdout.decode("utf8").strip(" \t\r\n")
	stderr_str = stderr.decode("utf8").strip(" \t\r\n")

	# profiler
	time_stop_sec_str = "({0:.2f} sec)".format(time.time() - time_start_sec)

	print(stdout_str)

	# rm extra warning info
	stderr_str = re.sub("^\d+ warnings generated\.", "", stderr_str).strip(" \t\r\n")
	stderr_str = re.sub("^\d+ warnings generated\.", "", stderr_str).strip(" \t\r\n")

	stderr_str = re.sub("^\d+ warnings and \d error generated\.", "", stderr_str).strip(" \t\r\n")
	self.traceError(stderr_str)

	if (self.isError(out, stderr_str)):
		if (options.STOP_ON_FAIL == 1):
			self.traceError("***** Detect errors. Commit stopped ***** " + time_stop_sec_str)
			sys.exit(1)
		else:
			self.traceError("***** Detect errors. Commited ***** " + time_stop_sec_str)
	else:
		self.traceOk("No warnings. OK " + time_stop_sec_str)
#else
	const std::vector<AnalyzersFactory::Type> analyzerTypes
	{
		AnalyzersFactory::Type::CppCheck,
		AnalyzersFactory::Type::ClangTidy
	};

	for (const auto &it_analyzerType : analyzerTypes) {
		auto &analyzer = AnalyzersFactory::create(it_analyzerType);
		analyzer->run();

	} // for (analyzerTypes)

	return ExitCode::Success;
#endif
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerApp::getComplierInfo() const
{
#if 0
def getComplierInfo(self):
	"" Get complier info (ID, name) ""

	cmd = "c++ --version".split()

	out = subprocess.Popen(cmd, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
	stdout,stderr = out.communicate()
	if (out.returncode == 1):
		self.traceError("getComplierInfo")
		return self.COMPILER_ID_UNKNOWN

	version_str = stdout.decode("utf8").strip();
	if (version_str.find("clang version") > 0):
		return self.COMPILER_ID_CLANG, "clang"
	else:
		return self.COMPILER_ID_GCC, "gcc"
#else

#endif
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerApp::getIncludeDirs() const
{
#if 0
def getIncludeDirs(self):
	"" Get include dirs ""

	result = ""

	if (options.TYPE_ACTIVE == options.TYPE_CPPCHECK and
		options.QUICK_CHECK == 1
	):
		result = ""
	else:
		"" System includes (cpp -v) ""
		if (1) :
			result = \
				self.getCompilerIncludeDirs() + " "
		else:
			result = \
				"-I/usr/lib/gcc/x86_64-linux-gnu/8/include " \
				"-I/usr/local/include " \
				"-I/usr/lib/gcc/x86_64-linux-gnu/8/include-fixed " \
				"-I/usr/include/x86_64-linux-gnu " \
				"-I/usr/include"

		result += \
			"-I/usr/local/include " + \
			"".join(self.getPkgConfig("libxml-2.0")) + " " + \
			"".join(self.getPkgConfig("ImageMagick")) + " " + \
			\
			"-I/usr/local/gen++v3/class " + \
			"-I" +       self.PROJECT_DIR + "/functions " + \
			"-isystem" + self.PROJECT_DIR + "/suppliers/gen/base " + \
			"-isystem" + self.PROJECT_DIR + "/booked/gen/base " + \
			"-isystem" + self.PROJECT_DIR + "/syntexts/gen/base " + \
			"-isystem" + self.PROJECT_DIR + "/core/gen/base " + \
			"-isystem" + self.PROJECT_DIR + "/api/gen/base " + \
			"-isystem" + self.PROJECT_DIR + "/seo/gen/base"
	return result
#else

#endif
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerApp::getCompilerIncludeDirs() const
{
#if 0
def getCompilerIncludeDirs(self):
	""  Get complier include dirs ""

	result = ""

	cmd = "cpp -v /dev/null".split()

	out = subprocess.Popen(cmd, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
	stdout,stderr = out.communicate()

	out_info = stderr.decode("utf8")

	str_left    = "#include <...> search starts here:"
	str_right   = "End of search list."

	pos_left  = out_info.find(str_left)
	pos_right = out_info.find(str_right, pos_left)
	assert pos_left < pos_right

	includes = out_info[int(pos_left) + len(str_left):int(pos_right)].strip().split()

	for it_include in includes:
		result += "-I" + it_include + " "

	if (self._os_name == "FreeBSD") :
		result += "-isystem/usr/include/c++/v1"

	return result
#else

#endif
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
	/// trace("TYPE_ACTIVE: " + self._name);
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
