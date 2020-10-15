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
	std::vec_tstring_t includeDirs;
	std::vec_tstring_t modifiedFiles;
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
