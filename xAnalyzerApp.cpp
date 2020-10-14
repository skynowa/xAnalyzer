/**
 * \file  xAnalyzerApp.cpp
 * \brief xAnalyzerApp
 */


#include "xAnalyzerApp.h"

//-------------------------------------------------------------------------------------------------
namespace
{
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_BEGIN(xa)
//-------------------------------------------------------------------------------------------------
xAnalyzerApp::xAnalyzerApp(
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
	xUNUSED(appArgs);

	// Cout() << xTRACE_VAR(appArgs);

	CmdOptions options;

	std::vector<CmdOptionsUsage> usage;
	options.parse(appArgs, usage);
#endif
}
//-------------------------------------------------------------------------------------------------
xAnalyzerApp::ExitCode
xAnalyzerApp::onRun() /* override */
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
	return ExitCode::Success;
#endif
}
//-------------------------------------------------------------------------------------------------
void_t
xAnalyzerApp::runCppcheck() const
{
#if 0
def runCppcheck(self):
	"" Run analysis Cppcheck ""

	cmd = \
		"cppcheck " \
		"{} {} " \
		"--library=std.cfg --library=posix.cfg " \
		"-UKERN_PROC_PATHNAME " \
		"--enable={} --inconclusive " \
		"--language=c --language={} --std={} " \
		"--platform=unix64 " \
		"--force " \
		"-j{} " \
		"--relative-paths " \
		"--error-exitcode=1" \
		.format(self._include_dirs, self._git_modified_files, options.CPPCHECK_ERROR_LEVEL,
			options.CPP_LANG, options.CPP_STD, self.JOBS_NUM) \
		.split()
	print("cmd: ", cmd)

	return subprocess.Popen(cmd, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
#else

#endif
}
//-------------------------------------------------------------------------------------------------
void_t
xAnalyzerApp::runClangTidy() const
{
#if 0
def runClangTidy(self):
	"" Run analysis by Clang-Tidy ""

	line_filter = "" # n/a

	args_stdlib = {
		self.COMPILER_ID_CLANG: "-stdlib=libstdc++",
		self.COMPILER_ID_GCC:   ""
	}

	force_cpp = "-x " + options.CPP_LANG

	header_filter = ""
	if (options.QUICK_CHECK == 1):
		header_filter = "" # skip
	else:
		header_filter = "^{}/.*".format(self.PROJECT_DIR) # all

	cmd = \
		"clang-tidy " \
		"{} " \
		"-system-headers=0 " \
		"-line-filter={} " \
		"-header-filter={} " \
		"-extra-arg=-std={} " \
		"-extra-arg={} " \
		"-quiet " \
		"-- " \
		"{} " \
		"{}" \
		.format(self._git_modified_files, line_filter, header_filter,
			options.CPP_STD, args_stdlib[self._complier_id], self._include_dirs,
			force_cpp) \
		.split()
	print("cmd: ", cmd)

	return subprocess.Popen(cmd, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
#else

#endif
}
//-------------------------------------------------------------------------------------------------
void_t
xAnalyzerApp::runClangTidyDiff() const
{
#if 0
def runClangTidyDiff(self):
	"" Run analysis by Clang-Tidy-Diff ""

	line_filter = self.getGitModifiedFilesLineFilter()

	args_stdlib = {
		self.COMPILER_ID_CLANG: "-stdlib=libstdc++",
		self.COMPILER_ID_GCC:   ""
	}

	force_cpp = "-x " + options.CPP_LANG

	header_filter = ""
	if (options.QUICK_CHECK == 1):
		header_filter = "" # skip
	else:
		header_filter = "^{}/.*".format(self.PROJECT_DIR) # all

	cmd = \
		"clang-tidy " \
		"{} " \
		"-system-headers=0 " \
		"-line-filter={} " \
		"-header-filter={} " \
		"-extra-arg=-std={} " \
		"-extra-arg={} " \
		"-quiet " \
		"-- " \
		"{} " \
		"{}" \
		.format(self._git_modified_files, line_filter, header_filter,
			options.CPP_STD, args_stdlib[self._complier_id], self._include_dirs,
			force_cpp) \
		.split()
	print("cmd: ", cmd)

	return subprocess.Popen(cmd, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
#else

#endif
}
//-------------------------------------------------------------------------------------------------
void_t
xAnalyzerApp::runClangTidyFile() const
{
#if 0
def runClangTidyFile(self):
	"" Run analysis by Clang-Tidy-File ""

	args_stdlib = {
		self.COMPILER_ID_CLANG: "-stdlib=libstdc++",
		self.COMPILER_ID_GCC:   ""
	}

	force_cpp = "-x " + options.CPP_LANG

	header_filter = ""
	if (options.QUICK_CHECK == 1):
		header_filter = "" # skip
	else:
		header_filter = "^{}/.*".format(self.PROJECT_DIR) # all

	cmd = \
		"clang-tidy " \
		"{} " \
		"-system-headers=0 " \
		"-header-filter={} " \
		"-extra-arg=-std={} " \
		"-extra-arg={} " \
		"-quiet " \
		"-- " \
		"{} " \
		"{}" \
		.format(self._file_to_check, header_filter,
			options.CPP_STD, args_stdlib[self._complier_id], self._include_dirs,
			force_cpp) \
		.split()
	print("cmd: ", cmd)

	return subprocess.Popen(cmd, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
#else

#endif
}
//-------------------------------------------------------------------------------------------------
void_t
xAnalyzerApp::getComplierInfo() const
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
xAnalyzerApp::getIncludeDirs() const
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
xAnalyzerApp::getCompilerIncludeDirs() const
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
xAnalyzerApp::getPkgConfig(
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
xAnalyzerApp::isError(
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
xAnalyzerApp::traceOptions() const
{
#if 0
def traceOptions(self):
	"" Trace options (confogs) ""

	print("")
	self.traceOk("Options:")
	print("TYPE_ACTIVE: ", self._name)
	print("COMPILER_ID: ", self._complier_name)
	print("QUICK_CHECK: ", options.QUICK_CHECK)
	print("SKIP_CHECK:  ", options.SKIP_CHECK)
	print("STOP_ON_FAIL:", options.STOP_ON_FAIL)
	print("CPP_STD:     ", options.CPP_STD)
	print("CPP_MASK:    ", ", ".join(options.CPP_MASK))
	print("")
#else

#endif
}
//-------------------------------------------------------------------------------------------------
void_t
xAnalyzerApp::traceColor(
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

#endif
}
//-------------------------------------------------------------------------------------------------
void_t
xAnalyzerApp::traceOk(
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

#endif
}
//-------------------------------------------------------------------------------------------------
void_t
xAnalyzerApp::traceError(
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

#endif
}
//-------------------------------------------------------------------------------------------------
xNAMESPACE_END(xa)
