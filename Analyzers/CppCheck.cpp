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
	IAnalyzer(Type::CppCheck, a_dataIn)
{
}
//-------------------------------------------------------------------------------------------------
void_t
CppCheck::run() /* override */
{
	// [in]
	// common
	std::tstring_t     projectDirPath = _dataIn.projectDirPath;
	std::tstring_t     cppLanguage    = _dataIn.cppLanguage;
	std::tstring_t     cppStandart    = _dataIn.cppStandart;
	std::ctstring_t    includeDirs    = String::join(_dataIn.includeDirs, " ");
	std::ctstring_t    modifiedFiles  = String::join(_dataIn.modifiedFiles, " ");
	std::ctstring_t    defines        = _dataIn.defines;
	::cCompilerId      compilerId     = _dataIn.compilerId;   xUNUSED(compilerId);
	SystemInfo::OsType osName         = _dataIn.osName;       xUNUSED(osName);
	cbool_t            isQuickCheck   = _dataIn.isQuickCheck; xUNUSED(isQuickCheck);


	// partial - CppCheck
	std::ctstring_t cLanguage      = _dataIn.cppCheck_cLanguage;
	std::csize_t    jobsNum        = _dataIn.cppCheck_jobsNum;
	std::ctstring_t errorLevel     = _dataIn.cppCheck_errorLevel;

	std::cvec_tstring_t params
	{
		includeDirs,
		modifiedFiles,
		"--library=std.cfg", "--library=posix.cfg",
		defines,
		"--enable=" + errorLevel, "--inconclusive",
		"--language=" + cLanguage, "--language=" + cppLanguage, "--std=" + cppStandart,
		"--platform=unix64",
		"--force",
		"-j" + std::to_string(jobsNum),
		"--relative-paths",
		"--error-exitcode=1",

		"--xml", "--xml-version=2"
	};

	std::tstring_t stdOut;
	std::tstring_t stdError;

	Process::execute(_binPath(), params, {}, xTIMEOUT_INFINITE, &stdOut, &stdError);
#if 1
	Cout() << xTRACE_VAR(stdOut);
	Cout() << xTRACE_VAR(stdError);
#endif
}
//-------------------------------------------------------------------------------------------------
void_t
CppCheck::_parseReport(
	std::ctstring_t &stdOut,
	std::ctstring_t &stdError
) const /* override */
{
}
//-------------------------------------------------------------------------------------------------
} // namespace xa
