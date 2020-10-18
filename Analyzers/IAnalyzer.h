/**
 * \file  IAnalyzer.h
 * \brief Analyzers interface
 */


#pragma once

#include "../Config.h"
//-------------------------------------------------------------------------------------------------
namespace xa
{

struct AnalyzerDataIn
{
	// common
	std::tstring_t     cppLanguage;
	std::tstring_t     cppStandart;
	std::vec_tstring_t includeDirs;
	std::vec_tstring_t modifiedFiles;

	// partial - CppCheck
	std::tstring_t     cLanguage;
	std::size_t        jobsNum;
};
xUSING_CONST(AnalyzerDataIn);

class IAnalyzer
    /// Analyzers interface
{
public:
///@name ctors, dtor
///@{
             IAnalyzer(cAnalyzerDataIn &dataIn);
    virtual ~IAnalyzer();

    xNO_COPY_ASSIGN(IAnalyzer)
///@}

    virtual void_t run() = 0;

protected:
	cAnalyzerDataIn _dataIn;
};

} // namespace xa
//-------------------------------------------------------------------------------------------------
