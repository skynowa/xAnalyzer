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

		analyzer->run();

		// TODO: stdOut, stdError - fill

		stdOut   = ::String::trimSpace(stdOut);
		stdError = ::String::trimSpace(stdError);

		// TODO: profiler
		std::ctstring_t time_stop_sec_str = "";
		/// time_stop_sec_str = "({0:.2f} sec)".format(time.time() - time_start_sec);

		trace(stdOut);

		// rm extra warning info
		/// stdOut   = re.sub("^\d+ warnings generated\.", "", stderr_str).strip(" \t\r\n");
		/// stdError = re.sub("^\d+ warnings generated\.", "", stderr_str).strip(" \t\r\n");

		/// stdError = re.sub("^\d+ warnings and \d error generated\.", "", stdError).strip(" \t\r\n");
		traceError(stdError);

		if ( isError(stdOut, stdError) ) {
			if (::STOP_ON_FAIL) {
				traceError("***** Detect errors. Commit stopped ***** " + time_stop_sec_str);

				return ExitCode::Failure;
			}

			traceError("***** Detect errors. Commited ***** " + time_stop_sec_str);
		} else {
			traceOk("No warnings. OK " + time_stop_sec_str);
		}
	} // for (analyzerTypes)

	return ExitCode::Success;
}
//-------------------------------------------------------------------------------------------------
bool_t
AnalyzerApp::isError(
	std::ctstring_t &a_out,
	std::ctstring_t &a_stderr_str
) const
{
#if 0
def isError(self, a_out, a_stderr_str):
	"" Check if errors detected ""

	return
		bool((a_out.returncode == 1 or
			  re.search("^.*(error|warning).*$", a_stderr_str, re.MULTILINE)) and
		a_stderr_str.find("Error while processing") > 0)
#else
	return false;
#endif
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
