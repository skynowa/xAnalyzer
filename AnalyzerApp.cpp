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
	_console.setEscapeValues(false);
}
//-------------------------------------------------------------------------------------------------
AnalyzerApp::ExitCode
AnalyzerApp::onRun() /* override */
{
	if (::SKIP_CHECK) {
		return Application::ExitCode::Success;
	}

	// profiler
	/// time_start_sec = time.time();

	AnalyzerDataIn dataIn;
	if ( dataIn.modifiedFiles.empty() ) {
		traceOk("No changes. OK");
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
				traceError("***** Detect errors. Commit stopped ***** ");

				return ExitCode::Failure;
			}

			traceError("***** Detect errors. Commited ***** ");
		} else {
			traceOk("No warnings. OK ");
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
		traceOk("Start analysis (quick)...");
	} else {
		traceOk("Start analysis (full)...");
	}

	trace("");
	traceOk("Options:");
	trace("SKIP_CHECK:  " + std::to_string(::SKIP_CHECK));
	trace("STOP_ON_FAIL:" + std::to_string(::STOP_ON_FAIL));
	trace("");
#endif
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerApp::traceColor(
	Console::Foreground  a_color,
	std::ctstring_t     &a_msg
) const
{
	xCHECK_DO(a_msg.empty(), return);

#if 0
	_console.writeLine(a_color, Console::Background::Default,
		static_cast<int_t>(Console::Attribute::Bold), _name + " " + a_msg);
#endif
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerApp::trace(
	std::ctstring_t &a_msg
) const
{
	_console.writeLine(a_msg);
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerApp::traceOk(
	std::ctstring_t &a_msg
) const
{
	xCHECK_DO(a_msg.empty(), return);

#if 0
	traceColor(Console::Foreground::Yellow, _name);
	traceColor(Console::Foreground::Green, " " + a_msg);
#endif
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerApp::traceError(
	std::ctstring_t &a_msg
) const
{
	xCHECK_DO(a_msg.empty(), return);

#if 0
	_console.traceColor(Console::Foreground::Red, _name + " " + a_msg);
#endif
}
//-------------------------------------------------------------------------------------------------
} // namespace xa
