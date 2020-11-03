/**
 * \file  AnalyzerDataIn.h
 * \brief Analyzers incoming data
 */


#include "AnalyzerDataIn.h"

namespace xa
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
AnalyzerDataIn::AnalyzerDataIn()
{
	// common
	projectDirPath      = ::PROJECT_DIR;
	cppLanguage         = ::CPP_LANG;
	cppStandart         = ::CPP_STD;
	_includeDirs(&includeDirs);
#if xANALYZER_DEBUG
	modifiedFiles       = {"/home/skynowa/Projects/xAnalyzer/Tests/Test_1.cpp"};
#else
	GitClient().modifiedFiles(::CPP_MASK, &modifiedFiles);
#endif
	defines             = "-UKERN_PROC_PATHNAME";
	_complierInfo(&compilerId, &compilerName);	xUNUSED(compilerName);
	osName              = SystemInfo().os();
	isSkipCheck         = ::SKIP_CHECK;
	isStopOnFail        = ::STOP_ON_FAIL;
	isQuickCheck        = ::QUICK_CHECK;

	// partial - CppCheck
	cppCheck_cLanguage  = ::C_LANG;
	cppCheck_jobsNum    = ::JOBS_NUM;
	cppCheck_errorLevel = ::CPPCHECK_ERROR_LEVEL;
}
//-------------------------------------------------------------------------------------------------
bool_t
AnalyzerDataIn::isValid() const /* override */
{
	// common
	xCHECK_RET(!Dir(projectDirPath).isExists(), false);
	xCHECK_RET(cppLanguage.empty(), false);
	xCHECK_RET(cppStandart.empty(), false);
	xTEST_NA(includeDirs);
	xTEST_NA(modifiedFiles);
	xTEST_NA(defines);
	xCHECK_RET(osName == SystemInfo::OsType::Unknown, false);
	xTEST_NA(compilerId);
	xCHECK_RET(compilerName.empty(), false);
	xTEST_NA(isQuickCheck);
	xTEST_NA(isSkipCheck);
	xTEST_NA(isStopOnFail);

	// partial - CppCheck
	xCHECK_RET(cppCheck_cLanguage.empty(), false);
	xCHECK_RET(cppCheck_jobsNum == 0, false);
	xCHECK_RET(cppCheck_errorLevel.empty(), false);

	return true;
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerDataIn::clear() /* override */
{
	// common
	projectDirPath      = {};
	cppLanguage         = {};
	cppStandart         = {};
	includeDirs         = {};
	modifiedFiles       = {};
	defines             = {};
	osName              = {};
	compilerId          = {};
	compilerName        = {};
	isSkipCheck         = {};
	isStopOnFail        = {};
	isQuickCheck        = {};

	// partial - CppCheck
	cppCheck_cLanguage  = {};
	cppCheck_jobsNum    = {};
	cppCheck_errorLevel = {};
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerDataIn::print(
	core::OStream &a_os
) const /* override */
{
#if 0
	if (isSkipCheck) {
		_log.writeOk("Start analysis (quick)...");
	} else {
		_log.writeOk("Start analysis (full)...");
	}
#endif

	a_os
		// common
		<< "\n"
		<< "DataIn:"                                 << "\n"
		<< "    " << xTRACE_VAR(projectDirPath)      << "\n"
		<< "    " << xTRACE_VAR(cppLanguage)         << "\n"
		<< "    " << xTRACE_VAR(cppStandart)         << "\n"
		<< "    " << xTRACE_VAR(includeDirs)         << "\n"
		<< "    " << xTRACE_VAR(modifiedFiles)       << "\n"
		<< "    " << xTRACE_VAR(defines)             << "\n"
		<< "    " << xTRACE_VAR((int)osName)         << "\n"
		<< "    " << xTRACE_VAR((int)compilerId)     << "\n"
		<< "    " << xTRACE_VAR(compilerName)        << "\n"
		<< "    " << xTRACE_VAR(isSkipCheck)         << "\n"
		<< "    " << xTRACE_VAR(isStopOnFail)        << "\n"
		<< "    " << xTRACE_VAR(isQuickCheck)        << "\n"
		<< "\n"
		// partial - CppCheck
		<< "    " << xTRACE_VAR(cppCheck_cLanguage)  << "\n"
		<< "    " << xTRACE_VAR(cppCheck_jobsNum)    << "\n"
		<< "    " << xTRACE_VAR(cppCheck_errorLevel);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   priivate
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
AnalyzerDataIn::_complierInfo(
	CompilerId     *out_complier_id,
	std::tstring_t *out_complier_name
) const
{
	xCHECK_DO(out_complier_id == nullptr, return);
	xCHECK_DO(out_complier_name == nullptr, return);

	*out_complier_id   = {};
	*out_complier_name = {};

	std::cvec_tstring_t params
	{
		"--version"
	};

	std::tstring_t stdOut;
	std::tstring_t stdError;

	Process::execute("/usr/bin/c++", params, {}, xTIMEOUT_INFINITE, &stdOut, &stdError);
#if 0
	Cout() << xTRACE_VAR(stdOut);
	Cout() << xTRACE_VAR(stdError);
#endif

#if 0
	if (out.returncode == 1):
		self.traceError("complierInfo")
		return self.COMPILER_ID_UNKNOWN
#endif

	std::ctstring_t &versionStr = String::trimSpace(stdOut);
	if (versionStr.find("clang version") != std::tstring_t::npos) {
		*out_complier_id   = CompilerId::Clang;
		*out_complier_name = "clang";
	} else {
		*out_complier_id   = CompilerId::Gcc;
		*out_complier_name = "gcc";
	}
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerDataIn::_includeDirs(
	std::vec_tstring_t *out_dirPathes
) const
{
	xCHECK_DO(out_dirPathes == nullptr, return);

	out_dirPathes->clear();

	// compiler includes
	{
		std::vec_tstring_t dirPathes;
		_compilerIncludeDirs(&dirPathes);

		*out_dirPathes = dirPathes;
	}

	// libxml
	{
	#if 0
		std::vec_tstring_t cflags;
		_pkgConfig("libxml-2.0", &cflags);

		out_dirPathes->insert(out_dirPathes->end(), cflags.cbegin(), cflags.cend());
	#endif
	}

	// ImageMagick
	{
	#if 0
		std::vec_tstring_t cflags;
		_pkgConfig("ImageMagick", &cflags);

		out_dirPathes->insert(out_dirPathes->end(), cflags.cbegin(), cflags.cend());
	#endif
	}

	// Custom
	{
	#if 1
		std::vec_tstring_t dirPathes
		{
		#if 0
			"-I/usr/local/include",
			"-I/usr/local/gen++v3/class",
			"-I" +       projectDirPath + "/functions",
			"-isystem" + projectDirPath + "/suppliers/gen/base",
			"-isystem" + projectDirPath + "/booked/gen/base",
			"-isystem" + projectDirPath + "/syntexts/gen/base",
			"-isystem" + projectDirPath + "/core/gen/base",
			"-isystem" + projectDirPath + "/api/gen/base",
			"-isystem" + projectDirPath + "/seo/gen/base"
		#else
			#if 0
				"-I /usr/include/c++/7",
				"-I/home/skynowa/Projects/xLib/Include"
			#endif
		#endif
		};

		out_dirPathes->insert(out_dirPathes->end(), dirPathes.cbegin(), dirPathes.cend());
	#endif
	}
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerDataIn::_compilerIncludeDirs(
	std::vec_tstring_t *out_dirPathes
) const
{
	xCHECK_DO(out_dirPathes == nullptr, return);

	out_dirPathes->clear();

	// System includes (cpp -v)
	std::cvec_tstring_t params
	{
		"-v",
		"/dev/null"
	};

	std::tstring_t stdOut;
	std::tstring_t stdError;

	Process::execute("/usr/bin/cpp", params, {}, xTIMEOUT_INFINITE, &stdOut, &stdError);
	xUNUSED(stdOut);
#if 0
	Cout() << xTRACE_VAR(stdOut);
	Cout() << xTRACE_VAR(stdError);
#endif

	std::ctstring_t strLeft  = "#include <...> search starts here:";
	std::ctstring_t strRight = "End of search list.";

	std::csize_t posLeft  = stdError.find(strLeft);
	std::csize_t posRight = stdError.find(strRight, posLeft);
	xTEST_LESS(posLeft, posRight);

	stdError = String::trimSpace( String::cut(stdError, strLeft, strRight) );

	std::vec_tstring_t includes;
	String::split(stdError, Const::nl(), &includes);

	for (const auto &it_include : includes) {
		out_dirPathes->push_back("-I" + String::trimSpace(it_include));
	}

	if (SystemInfo().os() == SystemInfo::OsType::FreeBSD) {
		out_dirPathes->push_back("-isystem/usr/include/c++/v1");
	}
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerDataIn::_pkgConfig(
	std::ctstring_t    &a_lib_name,
	std::vec_tstring_t *out_cflags
) const
{
	xTEST(!a_lib_name.empty());
	xTEST_PTR(out_cflags);

	out_cflags->clear();

	std::cvec_tstring_t paramsCflags
	{
		"--cflags-only-I",
		a_lib_name
	};

	std::tstring_t stdOut;
	std::tstring_t stdError;

	Process::execute("/usr/bin/pkg-config", paramsCflags, {}, xTIMEOUT_INFINITE, &stdOut, &stdError);
#if 0
	Cout() << xTRACE_VAR(stdOut);
	Cout() << xTRACE_VAR(stdError);
#endif

	// suppress all warnings
	stdOut = String::replaceAll(String::trimSpace(stdOut), "-I", "-isystem");

	String::split(stdOut, Const::nl(), out_cflags);
	if ( out_cflags->empty() ) {
		/// traceError("pkg-config: " + a_lib_name + " - fail");
		return;
	}
}
//-------------------------------------------------------------------------------------------------

} // namespace xa
