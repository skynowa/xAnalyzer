/**
 * \file  CppCheck.h
 * \brief CppCheck
 */


#pragma once

#include "../Config.h"
//-------------------------------------------------------------------------------------------------
namespace xa
{

class IAnalyzer
    ///
{
public:
///@name ctors, dtor
///@{
             IAnalyzer() = default;
    virtual ~IAnalyzer() = default;

    /// xNO_COPY_ASSIGN(IAnalyzer)
///@}

    virtual void_t run() = 0;
};

} // namespace xa
//-------------------------------------------------------------------------------------------------
