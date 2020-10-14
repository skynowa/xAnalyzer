/**
 * \file  ClangTidy.h
 * \brief ClangTidy
 */


#pragma once

#include <xLib/Core/Core.h>
#include "IAnalyzer.h"
//-------------------------------------------------------------------------------------------------
namespace xa
{

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

	void_t run() override;

private:

};

} // namespace xa
//-------------------------------------------------------------------------------------------------
