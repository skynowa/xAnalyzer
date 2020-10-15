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
             ClangTidy(cAnalyzerDataIn &dataIn);
    virtual ~ClangTidy();

    xNO_COPY_ASSIGN(ClangTidy)
///@}

	void_t run() override;

	void_t runDiff() const;
		///< run analysis for Git diff
	void_t runFile() const;
		///< run analysis for whole file

private:

};

} // namespace xa
//-------------------------------------------------------------------------------------------------
