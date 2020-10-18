/**
 * \file  IAnalyzer.h
 * \brief Analyzers interface
 */


#include "IAnalyzer.h"

namespace xa
{

//-------------------------------------------------------------------------------------------------
IAnalyzer::IAnalyzer(
	cTypeActive      a_type,
	cAnalyzerDataIn &a_dataIn
) :
	_type  {a_type},
	_dataIn{a_dataIn}
{
}
//-------------------------------------------------------------------------------------------------
IAnalyzer::~IAnalyzer()
{
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   priivate
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
AnalyzerDataIn::_complierInfo(
	::CompilerId   *out_complier_id,
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
		*out_complier_id   = ::CompilerId::Clang;
		*out_complier_name = "clang";
	} else {
		*out_complier_id   = ::CompilerId::Gcc;
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

	if (::TypeActive::Active == ::TypeActive::CppCheck &&
		::QUICK_CHECK)
	{
		*out_dirPathes = {};
	} else {
		if (true) {
			std::vec_tstring_t dirPathes;
			_compilerIncludeDirs(&dirPathes);

			*out_dirPathes = dirPathes;
		} else {
			*out_dirPathes =
				{
					"-I/usr/lib/gcc/x86_64-linux-gnu/8/include",
					"-I/usr/local/include",
					"-I/usr/lib/gcc/x86_64-linux-gnu/8/include-fixed",
					"-I/usr/include/x86_64-linux-gnu",
					"-I/usr/include"
				};
		}

		// libxml
		{
			std::vec_tstring_t cflags;
			_pkgConfig("libxml-2.0", &cflags);
			out_dirPathes->insert(out_dirPathes->end(), cflags.cbegin(), cflags.cend());
		}

		// ImageMagick
		{
			std::vec_tstring_t cflags;
			_pkgConfig("ImageMagick", &cflags);
			out_dirPathes->insert(out_dirPathes->end(), cflags.cbegin(), cflags.cend());
		}

		std::vec_tstring_t dirPathes
		{
			"-I/usr/local/include ",

			"-I/usr/local/gen++v3/class",
			"-I" +       ::PROJECT_DIR + "/functions",
			"-isystem" + ::PROJECT_DIR + "/suppliers/gen/base",
			"-isystem" + ::PROJECT_DIR + "/booked/gen/base",
			"-isystem" + ::PROJECT_DIR + "/syntexts/gen/base",
			"-isystem" + ::PROJECT_DIR + "/core/gen/base",
			"-isystem" + ::PROJECT_DIR + "/api/gen/base",
			"-isystem" + ::PROJECT_DIR + "/seo/gen/base"
		};

		out_dirPathes->insert(out_dirPathes->end(), dirPathes.cbegin(), dirPathes.cend());
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


/**************************************************************************************************
*   protected
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::tstring_t
IAnalyzer::_binPath() const
{
	std::tstring_t sRv;

	static const std::map<::TypeActive, std::vec_tstring_t> dirPaths
	{
		{
			::TypeActive::CppCheck,
			{
			#if   xENV_WIN
				// echo %Path%
				xT("c:\\Program Files (x86)\\CppCheck\\bin")
			#elif xENV_UNIX
				// echo $PATH
				xT("/usr/bin"),
				xT("/usr/local/bin")
			#endif
			}
		},
		{
			::TypeActive::ClangTidy,
			{
			#if   xENV_WIN
				// echo %Path%
				xT("c:\\Program Files (x86)\\clang-tidy\\bin")
			#elif xENV_UNIX
				// echo $PATH
				xT("/usr/bin"),
				xT("/usr/local/bin")
			#endif
			}
		}
	};

	static const std::map<::TypeActive, std::tstring_t> binNames
	{
		{
			::TypeActive::CppCheck,
		#if   xENV_WIN
			xT("cppcheck.exe")
		#elif xENV_UNIX
			xT("cppcheck")
		#endif
		},
		{
			::TypeActive::ClangTidy,
		#if   xENV_WIN
			xT("clang-tidy.exe")
		#elif xENV_UNIX
			xT("clang-tidy")
		#endif
		}
	};

	cbool_t isRecursively {false};

	sRv = Finder::file(dirPaths.find(_type)->second, binNames.find(_type)->second, isRecursively);
	xTEST(!sRv.empty());

	return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace xa
