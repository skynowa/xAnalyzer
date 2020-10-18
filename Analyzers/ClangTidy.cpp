/**
 * \file  ClangTidy.cpp
 * \brief ClangTidy
 */


#include "ClangTidy.h"


namespace xa
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
ClangTidy::ClangTidy(
	cAnalyzerDataIn &a_dataIn
) :
	IAnalyzer(Type::ClangTidy, a_dataIn)
{
}
//-------------------------------------------------------------------------------------------------
void_t
ClangTidy::run() /* override */
{
	// [in]
	// common
	std::tstring_t     projectDirPath = _dataIn.projectDirPath;
	std::ctstring_t    cppLanguage    = _dataIn.cppLanguage;
	std::ctstring_t    cppStandart    = _dataIn.cppStandart;
	std::ctstring_t    includeDirs    = String::join(_dataIn.includeDirs, " ");
	std::ctstring_t    modifiedFiles  = String::join(_dataIn.modifiedFiles, " ");
	std::ctstring_t    defines        = _dataIn.defines; xUNUSED(defines); // TODO: impl
	::cCompilerId      compilerId     = _dataIn.compilerId;
	SystemInfo::OsType osName         = _dataIn.osName;  xUNUSED(osName);
	cbool_t            isQuickCheck   = _dataIn.isQuickCheck;

	// partial - ClangTidy

	std::ctstring_t lineFilter = ""; // n/a

	std::map<::CompilerId, std::tstring_t> argsStdlib
	{
		{::CompilerId::Clang, "-stdlib=libstdc++"},
		{::CompilerId::Gcc,   ""}
	};

	std::ctstring_t forceCpp = "-x " + cppLanguage;

	std::tstring_t headerFilter;
	if (isQuickCheck) {
		headerFilter = ""; // skip
	} else {
		headerFilter = Format::str("^{}/.*", projectDirPath); // all
	}

	std::cvec_tstring_t params
	{
		modifiedFiles,
		"-system-headers=0",
		"-line-filter="    + lineFilter,
		"-header-filter="  + headerFilter,
		"-extra-arg=-std=" + cppStandart,
		"-extra-arg="      + argsStdlib[compilerId],
		"-quiet",
		"--",
		includeDirs,
		forceCpp
	};

	std::tstring_t stdOut;
	std::tstring_t stdError;

	Process::execute(_binPath(), params, {}, xTIMEOUT_INFINITE, &stdOut, &stdError);

	_parseReport(stdOut, stdError);
}
//-------------------------------------------------------------------------------------------------
void_t
ClangTidy::runDiff() const
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
ClangTidy::runFile() const
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
	// _file_to_check - file to check for manual run
#endif
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
ClangTidy::_parseReport(
	std::ctstring_t &a_stdOut,
	std::ctstring_t &a_stdError
) const /* override */
{
#if 1
	Cout() << xTRACE_VAR(a_stdOut);
	Cout() << xTRACE_VAR(a_stdError);
#endif

	std::tstring_t stdOut   = ::String::trimSpace(a_stdOut);
	std::tstring_t stdError = ::String::trimSpace(a_stdError);

	/// trace(stdOut);

	// rm extra warning info
	/// stdOut   = re.sub("^\d+ warnings generated\.", "", stderr_str).strip(" \t\r\n");
	/// stdError = re.sub("^\d+ warnings generated\.", "", stderr_str).strip(" \t\r\n");

	/// stdError = re.sub("^\d+ warnings and \d error generated\.", "", stdError).strip(" \t\r\n");
	/// traceError(stdError);

	bool_t bRv = _isError(a_stdOut, a_stdError);
	if (bRv) {

	}
}
//-------------------------------------------------------------------------------------------------
bool_t
ClangTidy::_isError(
	std::ctstring_t &stdOut,
	std::ctstring_t &stdError
) const /* override */
{
	return false;
}
//-------------------------------------------------------------------------------------------------
} // namespace xa
