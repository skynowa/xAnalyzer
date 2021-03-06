/**
 * \file  AnalyzerDataOut.h
 * \brief Analyzers outcoming data
 */


#include "AnalyzerDataOut.h"

namespace xa
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
AnalyzerDataOut::AnalyzerDataOut()
{
}
//-------------------------------------------------------------------------------------------------
bool_t
AnalyzerDataOut::isValid() const /* override */
{
	// common
#if 0
	xCHECK_RET(stdOut.empty(), false);
	xCHECK_RET(stdError.empty(), false);
#endif

	return true;
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerDataOut::clear() /* override */
{
	// common
	stdOut   = {};
	stdError = {};
}
//-------------------------------------------------------------------------------------------------
void_t
AnalyzerDataOut::print(
	core::OStream &a_os
) const /* override */
{
	a_os
		// common
		<< "\n"
		<< "DataOut:"                   << "\n"
		<< "    " << xTRACE_VAR(stdOut) << "\n"
		<< "    " << xTRACE_VAR(stdError);
}
//-------------------------------------------------------------------------------------------------

} // namespace xa
