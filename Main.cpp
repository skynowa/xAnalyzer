/**
 * \file  Main.cpp
 * \brief xAnalyzer
 */


#include "AnalyzerApp.h"

//-------------------------------------------------------------------------------------------------
int_t main(int_t a_argNum, tchar_t *a_args[])
{
#if 0
def main(argv):
	if (options.SKIP_CHECK == "1"):
		sys.exit(0)

	arguments_parser = argparse.ArgumentParser(description='Arguments:')
	arguments_parser.add_argument('--file-to-check', type=str, help='Optional. Full path to file to be checked.')

	try:
		analyzer = Analyzer(options.TYPE_ACTIVE)
		analyzer._file_to_check = arguments_parser.parse_args().file_to_check
		analyzer.run()
	except KeyboardInterrupt:
		print("Stopping...")
	finally:
		print("")

	sys.exit(0)
#else
	xUNUSED(a_argNum);
	xUNUSED(a_args);

	if (::SKIP_CHECK) {
		return Application::ExitCode::Success;
	}

	auto exitStatus {Application::ExitCode::Failure};

	try {
		xa::AnalyzerApp app(::appName, xT(""));
		exitStatus = app.run();
	}
	catch (const Exception &a_e) {
		Cout() << xTRACE_VAR_2(exitStatus, a_e.what());
	}
	catch (const std::exception &a_e) {
		Cout() << xTRACE_VAR_2(exitStatus, a_e.what());
	}
	catch (...) {
		Cout() << xTRACE_VAR_2(exitStatus, xT("Unknown error"));
	}

	return exitStatus;
#endif
}
//-------------------------------------------------------------------------------------------------
