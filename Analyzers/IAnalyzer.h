/**
 * \file  IAnalyzer.h
 * \brief Analyzers interface
 */


#pragma once

#include "../Config.h"

namespace xa
{
//-------------------------------------------------------------------------------------------------
struct AnalyzerDataIn
{
	// common
	std::tstring_t     projectDirPath;
	std::tstring_t     cppLanguage;
	std::tstring_t     cppStandart;
	std::vec_tstring_t includeDirs;
	std::vec_tstring_t modifiedFiles;
	std::tstring_t     defines;
	::CompilerId       compilerId {};

	// partial - CppCheck
	std::tstring_t     cppCheck_cLanguage;
	std::size_t        cppCheck_jobsNum {};
	std::tstring_t     cppCheck_errorLevel;
};
xUSING_CONST(AnalyzerDataIn);
//-------------------------------------------------------------------------------------------------
class IAnalyzer
    /// Analyzers interface
{
public:
///@name ctors, dtor
///@{
             IAnalyzer(cTypeActive type, cAnalyzerDataIn &dataIn);
    virtual ~IAnalyzer();

    xNO_COPY_ASSIGN(IAnalyzer)
///@}

    virtual void_t run() = 0;

protected:
	cTypeActive     _type {};
	cAnalyzerDataIn _dataIn {};

	std::tstring_t  _binPath() const;
		///< path to binary file
};
//-------------------------------------------------------------------------------------------------
} // namespace xa
