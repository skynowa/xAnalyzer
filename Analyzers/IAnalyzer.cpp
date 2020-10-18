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
