/**
 * \file  ClangTidy.cpp
 * \brief ClangTidy
 */


#include "ClangTidy.h"

#if   xENV_WIN
    #include "Platform/Win/ClangTidy_win.inl"
#elif xENV_UNIX
    // #include "Platform/Unix/ClangTidy_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/ClangTidy_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/ClangTidy_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Apple/ClangTidy_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xl, xa)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
ClangTidy::ClangTidy()
{
    _construct_impl();
}
//-------------------------------------------------------------------------------------------------
ClangTidy::~ClangTidy()
{
    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, xa)
