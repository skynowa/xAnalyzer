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

	bool_t run() override;

private:
	Log _log;

	void_t _parseReport(std::ctstring_t &stdOut, std::ctstring_t &stdError) const override;
	bool_t _isError(std::ctstring_t &stdOut, std::ctstring_t &stdError) const override;
};

} // namespace xa
//-------------------------------------------------------------------------------------------------
