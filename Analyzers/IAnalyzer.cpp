/**
 * \file  IAnalyzer.h
 * \brief Analyzers interface
 */


#include "IAnalyzer.h"

namespace xa
{

//-------------------------------------------------------------------------------------------------
IAnalyzer::IAnalyzer(
	cType            a_type,
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
std::tstring_t
IAnalyzer::_binPath() const
{
	static const std::map<Type, std::tstring_t> binNames
	{
		{Type::CppCheck,  xT("cppcheck")   + Path::fileDotExt(Path::FileExt::Exe)},
		{Type::ClangTidy, xT("clang-tidy") + Path::fileDotExt(Path::FileExt::Exe)}
	};

	cbool_t isRecursively {false};

	std::ctstring_t sRv = Finder::fileInEnvPath(binNames.find(_type)->second, isRecursively);
	xTEST(!sRv.empty());
	xTEST(FileInfo(sRv).isExists());

	return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace xa
