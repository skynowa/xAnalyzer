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
    virtual ~ClangTidy() = default;

    xNO_COPY_ASSIGN(ClangTidy)
///@}

	bool_t run(AnalyzerDataOut *dataOut) override;

	void_t runDiff() const;
		///< run analysis for Git diff
	void_t runFile() const;
		///< run analysis for whole file

private:
	Log _log;

	void_t _parseReport(AnalyzerDataOut *dataOut) const override;
	bool_t _isError(const AnalyzerDataOut &dataOut) const override;
};

} // namespace xa
//-------------------------------------------------------------------------------------------------
