/**
 * \file  ClangTidy.h
 * \brief ClangTidy
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, xa)

class ClangTidy
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


xPLATFORM_IMPL:
    void_t _construct_impl();
    void_t _destruct_impl();
};

xNAMESPACE_END2(xl, xa)
//-------------------------------------------------------------------------------------------------
