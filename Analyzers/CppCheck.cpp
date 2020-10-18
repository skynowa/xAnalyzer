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
CppCheck::~CppCheck()
{
}
//-------------------------------------------------------------------------------------------------
void_t
CppCheck::run() /* override */
{
	std::ctstring_t include_dirs       = String::join(_dataIn.includeDirs, " ");
	std::ctstring_t git_modified_files = String::join(_dataIn.modifiedFiles, " ");

	std::cvec_tstring_t params
	{
		include_dirs,
		git_modified_files,
		"--library=std.cfg", "--library=posix.cfg",
		/// "-UKERN_PROC_PATHNAME",
		"--enable=" + ::CPPCHECK_ERROR_LEVEL, "--inconclusive",
		"--language=c", "--language=" + ::CPP_LANG, "--std=" + ::CPP_STD,
		"--platform=unix64",
		"--force",
		"-j" + std::to_string(::JOBS_NUM),
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
