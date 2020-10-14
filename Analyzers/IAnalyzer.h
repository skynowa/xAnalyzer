/**
 * \file  IAnalyzer.h
 * \brief Analyzers interface
 */


#pragma once

#include "../Config.h"
//-------------------------------------------------------------------------------------------------
namespace xa
{

class IAnalyzer
    /// Analyzers interface
{
public:
///@name ctors, dtor
///@{
             IAnalyzer() = default;
    virtual ~IAnalyzer() = default;

    xNO_COPY_ASSIGN(IAnalyzer)
///@}

    virtual void_t run() = 0;
};

} // namespace xa
//-------------------------------------------------------------------------------------------------
