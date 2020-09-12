/**
 * \file  CppCheck.cpp
 * \brief CppCheck
 */


#include "CppCheck.h"

#if   xENV_WIN
    #include "Platform/Win/CppCheck_win.inl"
#elif xENV_UNIX
    // #include "Platform/Unix/CppCheck_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/CppCheck_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/CppCheck_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Apple/CppCheck_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xl, xa)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
CppCheck::CppCheck()
{
    _construct_impl();
}
//-------------------------------------------------------------------------------------------------
CppCheck::~CppCheck()
{
    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, xa)
