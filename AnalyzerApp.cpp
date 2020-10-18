/**
 * \file  AnalyzerApp.cpp
 * \brief AnalyzerApp
 */


#include "AnalyzerApp.h"

#include "Analyzers/IAnalyzer.h"
#include "Analyzers/ClangTidy.h"
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
}
//-------------------------------------------------------------------------------------------------
AnalyzerApp::ExitCode
AnalyzerApp::onRun() /* override */
{
	const AnalyzerDataIn dataIn;

	if (dataIn.isSkipCheck) {
		return Application::ExitCode::Success;
	}

	if ( dataIn.modifiedFiles.empty() ) {
		_log.writeOk("No changes. OK");
		return ExitCode::Success;
	}

	for (const auto &it_analyzerType : AnalyzersFactory::types()) {
		auto &analyzer = AnalyzersFactory::create(it_analyzerType, dataIn);

		if (it_analyzerType == IAnalyzer::Type::ClangTidy) {
			static_cast<ClangTidy &>(*analyzer).runDiff();
			static_cast<ClangTidy &>(*analyzer).runFile();
		}

		AnalyzerDataOut dataOut;
		bool_t bRv = analyzer->run(&dataOut);
		xUNUSED(dataOut);

		if (!bRv) {
			if (dataIn.isStopOnFail) {
				_log.writeError("***** Detect errors. Commit stopped ***** ");
				return ExitCode::Failure;
			}

			_log.writeError("***** Detect errors. Commited ***** ");
		} else {
			_log.writeOk("No warnings. OK ");
		}
	} // for (analyzerTypes)

	return ExitCode::Success;
}
//-------------------------------------------------------------------------------------------------

} // namespace xa
