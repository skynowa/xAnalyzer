/**
 * \file  AnalyzerApp.h
 * \brief AnalyzerApp
 */


#include <xLib/xLib.h>
#include "Config.h"
#include "Log.h"
//-------------------------------------------------------------------------------------------------
namespace xa
{

class AnalyzerApp :
	public Application
{
public:
///@name ctors, dtor
///@{
	AnalyzerApp(std::ctstring_t &appGuid, std::ctstring_t &locale);
	~AnalyzerApp() = default;

	xNO_COPY_ASSIGN(AnalyzerApp)
///@}

	ExitCode onRun() override;

private:
	Log _log;

	void_t traceOptions() const;
		///< trace options (configs)
};

} // namespace xa
//-------------------------------------------------------------------------------------------------
