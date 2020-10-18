/**
 * \file  CppCheck.cpp
 * \brief CppCheck
 */


#include "CppCheck.h"


namespace xa
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
CppCheck::CppCheck(
	cAnalyzerDataIn &a_dataIn
) :
	IAnalyzer(a_dataIn)
{
}
//-------------------------------------------------------------------------------------------------
void_t
CppCheck::run() /* override */
{
	// [in]
	// common
	std::tstring_t  cppLanguage        = _dataIn.cppLanguage;
	std::tstring_t  cppStandart        = _dataIn.cppStandart;
	std::ctstring_t include_dirs       = String::join(_dataIn.includeDirs, " ");
	std::ctstring_t git_modified_files = String::join(_dataIn.modifiedFiles, " ");

	// partial - CppCheck
	std::tstring_t  cLanguage          = _dataIn.cppCheck_cLanguage;
	std::size_t     jobsNum            = _dataIn.cppCheck_jobsNum;

	std::cvec_tstring_t params
	{
		include_dirs,
		git_modified_files,
		"--library=std.cfg", "--library=posix.cfg",
		/// "-UKERN_PROC_PATHNAME",
		"--enable=" + ::CPPCHECK_ERROR_LEVEL, "--inconclusive",
		"--language=" + cLanguage, "--language=" + cppLanguage, "--std=" + cppStandart,
		"--platform=unix64",
		"--force",
		"-j" + std::to_string(jobsNum),
		"--relative-paths",
		"--error-exitcode=1",

		"--xml", "--xml-version=2"
	};

	int i = 0;
	i = 1 / i;

	std::tstring_t stdOut;
	std::tstring_t stdError;

	Process::execute("/usr/bin/cppcheck", params, {}, xTIMEOUT_INFINITE, &stdOut, &stdError);
#if 1
	Cout() << xTRACE_VAR(stdOut);
	Cout() << xTRACE_VAR(stdError);
#endif
}
//-------------------------------------------------------------------------------------------------

} // namespace xa
