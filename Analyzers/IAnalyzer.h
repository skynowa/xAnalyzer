/**
 * \file  IAnalyzer.h
 * \brief Analyzers interface
 */


#pragma once

#include "../Config.h"
#include "AnalyzerDataIn.h"

namespace xa
{
//-------------------------------------------------------------------------------------------------
class IAnalyzer
    /// Analyzers interface
{
public:
///@name ctors, dtor
///@{
             IAnalyzer(cAnalyzerType type, cAnalyzerDataIn &dataIn);
    virtual ~IAnalyzer() = default;

    xNO_COPY_ASSIGN(IAnalyzer)
///@}

    virtual void_t run() = 0;

protected:
	cAnalyzerType     _type {};
	std::tstring_t  _name;
	cAnalyzerDataIn _dataIn;

	std::tstring_t  _binPath() const;
		///< path to binary file
};
//-------------------------------------------------------------------------------------------------
} // namespace xa
