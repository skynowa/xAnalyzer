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
bool_t
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
	std::ctstring_t    cLanguage      = _dataIn.cppCheck_cLanguage;
	std::csize_t       jobsNum        = _dataIn.cppCheck_jobsNum;
	std::ctstring_t    errorLevel     = _dataIn.cppCheck_errorLevel;

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

	_parseReport(stdOut, stdError);

	return _isError(stdOut, stdError);
}
//-------------------------------------------------------------------------------------------------
void_t
CppCheck::_parseReport(
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
}
//-------------------------------------------------------------------------------------------------
bool_t
CppCheck::_isError(
	std::ctstring_t &stdOut,
	std::ctstring_t &stdError
) const /* override */
{
	return false;
}
//-------------------------------------------------------------------------------------------------
} // namespace xa
