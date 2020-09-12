/**
 * \file  CppCheck.h
 * \brief CppCheck
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, xa)

class CppCheck
    /// CppCheck
{
public:
///@name ctors, dtor
///@{
             CppCheck();
    virtual ~CppCheck();

    xNO_COPY_ASSIGN(CppCheck)
///@}

private:


xPLATFORM_IMPL:
    void_t _construct_impl();
    void_t _destruct_impl();
};

xNAMESPACE_END2(xl, xa)
//-------------------------------------------------------------------------------------------------
