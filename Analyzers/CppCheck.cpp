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
	IAnalyzer(Type::CppCheck, a_dataIn),
	_log     (_dataIn.compilerName)
{
}
//-------------------------------------------------------------------------------------------------
bool_t
CppCheck::run(
	AnalyzerDataOut *out_dataOut
) /* override */
{
	bool_t bRv {};

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

	Process::execute(_binPath(), params, {}, xTIMEOUT_INFINITE, &out_dataOut->stdOut,
		&out_dataOut->stdError);
	xTEST(out_dataOut->isValid());

	_parseReport(out_dataOut);

	bRv = _isError(*out_dataOut);
	xCHECK_RET(!bRv, false);

	return true;
}
//-------------------------------------------------------------------------------------------------
void_t
CppCheck::_parseReport(
	AnalyzerDataOut *out_dataOut
) const /* override */
{
#if 1
	_log.write("a_stdOut: "   + out_dataOut->stdOut);
	_log.write("a_stdError: " + out_dataOut->stdError);
#endif

	std::tstring_t stdOut   = ::String::trimSpace(out_dataOut->stdOut);
	std::tstring_t stdError = ::String::trimSpace(out_dataOut->stdError);

	_log.write(stdOut);

	// rm extra warning info
	/// stdOut   = re.sub("^\d+ warnings generated\.", "", stderr_str).strip(" \t\r\n");
	/// stdError = re.sub("^\d+ warnings generated\.", "", stderr_str).strip(" \t\r\n");

	/// stdError = re.sub("^\d+ warnings and \d error generated\.", "", stdError).strip(" \t\r\n");
	_log.writeError(stdError);
}
//-------------------------------------------------------------------------------------------------
bool_t
CppCheck::_isError(
	const AnalyzerDataOut &a_dataOut
) const /* override */
{
#if 0
def isError(self, a_out, a_stderr_str):
	return
		bool((a_out.returncode == 1 or
			  re.search("^.*(error|warning).*$", a_stderr_str, re.MULTILINE)) and
		a_stderr_str.find("Error while processing") > 0)
#else
	return false;
#endif
}
//-------------------------------------------------------------------------------------------------
} // namespace xa
