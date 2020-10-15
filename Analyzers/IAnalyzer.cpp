/**
 * \file  IAnalyzer.h
 * \brief Analyzers interface
 */


#include "IAnalyzer.h"

namespace xa
{

//-------------------------------------------------------------------------------------------------
IAnalyzer::IAnalyzer(
	cAnalyzerDataIn &a_dataIn
) :
	_dataIn{a_dataIn}
{
}
//-------------------------------------------------------------------------------------------------
IAnalyzer::~IAnalyzer()
{
}
//-------------------------------------------------------------------------------------------------

} // namespace xa
