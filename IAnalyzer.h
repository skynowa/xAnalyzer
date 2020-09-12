/**
 * \file  CppCheck.h
 * \brief CppCheck
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, xa)

class IAnalyzer
    ///
{
public:
///@name ctors, dtor
///@{
             IAnalyzer() = default;
    virtual ~IAnalyzer() = default;

    xNO_COPY_ASSIGN(IAnalyzer)
///@}
};

xNAMESPACE_END2(xl, xa)
//-------------------------------------------------------------------------------------------------
