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
	if (::SKIP_CHECK) {
		return Application::ExitCode::Success;
	}

	AnalyzerDataIn dataIn;
	if ( dataIn.modifiedFiles.empty() ) {
		_log.writeOk("No changes. OK");
		return ExitCode::Success;
	}

	const std::vector<IAnalyzer::Type> analyzerTypes
	{
		IAnalyzer::Type::CppCheck,
		IAnalyzer::Type::ClangTidy
	};

	for (const auto &it_analyzerType : analyzerTypes) {
		auto &analyzer = AnalyzersFactory::create(it_analyzerType, dataIn);

		if (it_analyzerType == IAnalyzer::Type::ClangTidy) {
			static_cast<ClangTidy &>(*analyzer).runDiff();
			static_cast<ClangTidy &>(*analyzer).runFile();
		}

		std::tstring_t stdOut;
		std::tstring_t stdError;

		bool bRv = analyzer->run();

		// TODO: stdOut, stdError - fill

		if (!bRv) {
			if (::STOP_ON_FAIL) {
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
void_t
AnalyzerApp::traceOptions() const
{
#if 0
	if (::QUICK_CHECK) {
		_log.writeOk("Start analysis (quick)...");
	} else {
		_log.writeOk("Start analysis (full)...");
	}

	_log.write("");
	_log.writeOk("Options:");
	_log.write("SKIP_CHECK:  " + std::to_string(::SKIP_CHECK));
	_log.write("STOP_ON_FAIL:" + std::to_string(::STOP_ON_FAIL));
	_log.write("");
#endif
}
//-------------------------------------------------------------------------------------------------

} // namespace xa
