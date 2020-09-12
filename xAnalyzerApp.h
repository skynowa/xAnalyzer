/**
 * \file  Main.h
 * \brief GitPrompt
 */


#include <xLib/xLib.h>
#include "Config.h"
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(xa)

class xAnalyzerApp :
	public Application
{
public:
			 xAnalyzerApp(std::ctstring_t &appGuid, std::ctstring_t &locale);
			~xAnalyzerApp() = default;

	xNO_COPY_ASSIGN(xAnalyzerApp)

	ExitCode onRun() override;

private:

};

xNAMESPACE_END(xa)
//-------------------------------------------------------------------------------------------------
/**
 * TODO:
 *
 */
//-------------------------------------------------------------------------------------------------
