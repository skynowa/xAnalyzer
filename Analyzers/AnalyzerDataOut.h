/**
 * \file  AnalyzerDataOut.h
 * \brief Analyzers outcoming data
 */


#pragma once

#include "../Config.h"

namespace xa
{
//-------------------------------------------------------------------------------------------------
class AnalyzerDataOut :
	public IData
{
public:
	// common
	std::tstring_t stdOut;
	std::tstring_t stdError;

///@name ctors, dtor
///@{
	 AnalyzerDataOut();
	~AnalyzerDataOut() = default;
///@}

	bool_t isValid() const override;
	void_t clear() override;
	void_t print(core::OStream &os) const override;
};
xUSING_CONST(AnalyzerDataOut);
//-------------------------------------------------------------------------------------------------
} // namespace xa
