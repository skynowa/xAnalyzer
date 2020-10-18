/**
 * \file  AnalyzerApp.cpp
 * \brief AnalyzerApp
 */


#include "AnalyzerApp.h"

#include "Analyzers/IAnalyzer.h"
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

	// analyzer type
	_type = ::TypeActive::Active;

	// analyzer name
	std::map<::TypeActive, std::tstring_t> names
	{
		{::TypeActive::CppCheck,      "[Cppcheck]"},
		{::TypeActive::ClangTidy,     "[Clang-Tidy]"},
		{::TypeActive::ClangTidyDiff, "[Clang-Tidy-Diff]"},
		{::TypeActive::ClangTidyFile, "[Clang-Tidy-File]"}
	};

	_name = names[_type];
	if ( _name.empty() ) {
		traceError("Bad type: " + Enum::str(_type));
		Process::currentExit(1);
		return;
	}
}
//-------------------------------------------------------------------------------------------------
AnalyzerApp::ExitCode
AnalyzerApp::onRun() /* override */
{
	// profiler
	/// time_start_sec = time.time();

	// TODO: dataIn
	AnalyzerDataIn dataIn {};
	{
		// common
		dataIn.projectDirPath      = ::PROJECT_DIR;
		dataIn.cppLanguage         = ::CPP_LANG;
		dataIn.cppStandart         = ::CPP_STD;
		/// includeDirs(&dataIn.includeDirs);
		_git.modifiedFiles(::CPP_MASK, &dataIn.modifiedFiles);
		dataIn.defines             = "-UKERN_PROC_PATHNAME";
		std::tstring_t _complier_name;
		/// complierInfo(&dataIn.compilerId, &_complier_name);
		xUNUSED(_complier_name);
		dataIn.osName              = SystemInfo().os();
		dataIn.isQuickCheck        = ::QUICK_CHECK;

		// partial - CppCheck
		dataIn.cppCheck_cLanguage  = ::C_LANG;
		dataIn.cppCheck_jobsNum    = ::JOBS_NUM;
		dataIn.cppCheck_errorLevel = ::CPPCHECK_ERROR_LEVEL;

		traceOptions();

		if (dataIn.modifiedFiles.empty() &&
			_type != ::TypeActive::ClangTidyFile)
		{
			traceOk("No changes. OK");
			return ExitCode::Success;
		}
	}

	std::tstring_t stdOut;
	std::tstring_t stdError;
	{
		if (false) {
			const std::vector<AnalyzersFactory::Type> analyzerTypes
			{
				AnalyzersFactory::Type::CppCheck,
				AnalyzersFactory::Type::ClangTidy
			};

			for (const auto &it_analyzerType : analyzerTypes) {
				auto &analyzer = AnalyzersFactory::create(it_analyzerType, dataIn);
				analyzer->run();

			}
		}
		else {
			switch (_type) {
			case ::TypeActive::CppCheck:
				{
					auto &analyzer = AnalyzersFactory::create(AnalyzersFactory::Type::CppCheck, dataIn);
					analyzer->run();
				}
				break;
			case ::TypeActive::ClangTidy:
				{
					auto &analyzer = AnalyzersFactory::create(AnalyzersFactory::Type::ClangTidy, dataIn);
					analyzer->run();
				}
				break;
			case ::TypeActive::ClangTidyDiff:
				{
					auto &analyzer = AnalyzersFactory::create(AnalyzersFactory::Type::ClangTidy, dataIn);
					/// self.runClangTidyDiff();
					analyzer->run();
				}
				break;
			case ::TypeActive::ClangTidyFile:
				{
					auto &analyzer = AnalyzersFactory::create(AnalyzersFactory::Type::ClangTidy, dataIn);
					/// self.runClangTidyFile();
					analyzer->run();
				}
				break;
			}
		}

		// TODO: stdOut, stdError - fill

		stdOut   = ::String::trimSpace(stdOut);
		stdError = ::String::trimSpace(stdError);
	}

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
	if (::QUICK_CHECK) {
		traceOk("Start analysis (quick)...");
	} else {
		traceOk("Start analysis (full)...");
	}

	trace("");
	traceOk("Options:");
	trace("TYPE_ACTIVE: " + _name);
	/// trace("COMPILER_ID: " + _complier_name);
	trace("QUICK_CHECK: " + std::to_string(::QUICK_CHECK));
	trace("SKIP_CHECK:  " + std::to_string(::SKIP_CHECK));
	trace("STOP_ON_FAIL:" + std::to_string(::STOP_ON_FAIL));
	trace("CPP_STD:     " + ::CPP_STD);
	trace("CPP_MASK:    " + String::join(::CPP_MASK, ", "));
	trace("");
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerApp::traceColor(
	Console::Foreground  a_color,
	std::ctstring_t     &a_msg
) const
{
	xCHECK_DO(a_msg.empty(), return);

	std::ctstring_t str = _console.setAttributesText(a_color, Console::Background::Default,
		static_cast<int_t>(Console::Attribute::Bold), _name);

	_console.writeLine(str + " " + a_msg);
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

	std::tstring_t str;
	str = _console.setAttributesText(Console::Foreground::Yellow , Console::Background::Default,
		static_cast<int_t>(Console::Attribute::Bold), _name);
	str += _console.setAttributesText(Console::Foreground::Green , Console::Background::Default,
		static_cast<int_t>(Console::Attribute::Bold), " " + a_msg);

	_console.writeLine(str);
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerApp::traceError(
	std::ctstring_t &a_msg
) const
{
	xCHECK_DO(a_msg.empty(), return);

	std::ctstring_t str =
		_console.setAttributesText(Console::Foreground::Red , Console::Background::Default,
		static_cast<int_t>(Console::Attribute::Bold), _name + " " + a_msg);

	_console.writeLine(str);
}
//-------------------------------------------------------------------------------------------------
} // namespace xa
