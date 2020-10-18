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

	void_t run() override;

private:

};

} // namespace xa
//-------------------------------------------------------------------------------------------------
