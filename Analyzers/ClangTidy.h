/**
 * \file  ClangTidy.h
 * \brief ClangTidy
 */


#pragma once

#include <xLib/Core/Core.h>
#include "IAnalyzer.h"
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, xa)

class ClangTidy :
    public IAnalyzer
    /// ClangTidy
{
public:
///@name ctors, dtor
///@{
             ClangTidy();
    virtual ~ClangTidy();

    xNO_COPY_ASSIGN(ClangTidy)
///@}

private:

};

xNAMESPACE_END2(xl, xa)
//-------------------------------------------------------------------------------------------------
