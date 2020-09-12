/**
 * \file  Main.cpp
 * \brief GitPrompt
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
	std::vec_tstring_t appArgs;
	args(true, &appArgs);
	xUNUSED(appArgs);

	// Cout() << xTRACE_VAR(appArgs);

	CmdOptions options;

	std::vector<CmdOptionsUsage> usage;
	options.parse(appArgs, usage);
}
//-------------------------------------------------------------------------------------------------
xAnalyzerApp::ExitCode
xAnalyzerApp::onRun() /* override */
{
	return ExitCode::Success;
}
//-------------------------------------------------------------------------------------------------
xNAMESPACE_END(xa)
