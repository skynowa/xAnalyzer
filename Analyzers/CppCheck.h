/**
 * \file  CppCheck.h
 * \brief CppCheck
 */


#pragma once

#include <xLib/Core/Core.h>
#include "IAnalyzer.h"
//-------------------------------------------------------------------------------------------------
namespace xa
{

class CppCheck :
    public IAnalyzer
    /// CppCheck
{
public:
///@name ctors, dtor
///@{
             CppCheck(cAnalyzerDataIn &dataIn);
    virtual ~CppCheck() = default;

    xNO_COPY_ASSIGN(CppCheck)
///@}

	bool_t run(AnalyzerDataOut *dataOut) override;

private:
	Log _log;

	void_t _parseReport(AnalyzerDataOut *dataOut) const override;
	bool_t _isError(const AnalyzerDataOut &dataOut) const override;
};

} // namespace xa
//-------------------------------------------------------------------------------------------------
