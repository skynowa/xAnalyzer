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
	IAnalyzer(a_dataIn)
{
}
//-------------------------------------------------------------------------------------------------
void_t
ClangTidy::run() /* override */
{
	// [in]
	// common
	std::ctstring_t cppLanguage   = _dataIn.cppLanguage;
	std::ctstring_t cppStandart   = _dataIn.cppStandart;
	std::ctstring_t includeDirs   = String::join(_dataIn.includeDirs, " ");
	std::ctstring_t modifiedFiles = String::join(_dataIn.modifiedFiles, " ");

	// partial - ClangTidy

	// TODO: complier_id - impl
	const auto complierId = ::CompilerId::Unknown;

	std::ctstring_t line_filter = ""; // n/a

	std::map<::CompilerId, std::tstring_t> args_stdlib
	{
		{::CompilerId::Clang, "-stdlib=libstdc++"},
		{::CompilerId::Gcc,   ""}
	};

	std::ctstring_t force_cpp = "-x " + cppLanguage;

	std::tstring_t header_filter;
	if (::QUICK_CHECK) {
		header_filter = ""; // skip
	} else {
		header_filter = Format::str("^{}/.*", ::PROJECT_DIR); // all
	}

	std::cvec_tstring_t params
	{
		modifiedFiles,
		"-system-headers=0",
		"-line-filter="    + line_filter,
		"-header-filter="  + header_filter,
		"-extra-arg=-std=" + cppStandart,
		"-extra-arg="      + args_stdlib[complierId],
		"-quiet",
		"--",
		includeDirs,
		force_cpp
	};

	std::tstring_t stdOut;
	std::tstring_t stdError;

	Process::execute("/usr/bin/clang-tidy", params, {}, xTIMEOUT_INFINITE, &stdOut, &stdError);
#if 1
	Cout() << xTRACE_VAR(stdOut);
	Cout() << xTRACE_VAR(stdError);
#endif
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

} // namespace xa
