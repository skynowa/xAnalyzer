/**
 * \file  IAnalyzer.h
 * \brief Analyzers interface
 */


#include "IAnalyzer.h"

namespace xa
{

//-------------------------------------------------------------------------------------------------
IAnalyzer::IAnalyzer(
	cType      a_type,
	cAnalyzerDataIn &a_dataIn
) :
	_type  {a_type},
	_dataIn{a_dataIn}
{
	// analyzer name
	std::map<Type, std::tstring_t> names
	{
		{Type::CppCheck,  "[Cppcheck]"},
		{Type::ClangTidy, "[Clang-Tidy]"}
	};

	_name = names[_type];
	if ( _name.empty() ) {
		/// traceError("Bad type: " + Enum::str(_type));
		Process::currentExit(1);
		return;
	}
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   protected
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
std::vector<IAnalyzer::Type>
IAnalyzer::types()
{
	static const std::vector<Type> types
	{
		Type::CppCheck,
		Type::ClangTidy
	};

	return types;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
IAnalyzer::_binPath() const
{
	std::tstring_t sRv;

	static const std::map<Type, std::vec_tstring_t> dirPaths
	{
		{
			Type::CppCheck,
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
			Type::ClangTidy,
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

	static const std::map<Type, std::tstring_t> binNames
	{
		{
			Type::CppCheck,
		#if   xENV_WIN
			xT("cppcheck.exe")
		#elif xENV_UNIX
			xT("cppcheck")
		#endif
		},
		{
			Type::ClangTidy,
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
