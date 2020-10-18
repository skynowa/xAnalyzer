/**
 * \file  AnalyzerApp.h
 * \brief AnalyzerApp
 */


#include <xLib/xLib.h>
#include "Config.h"
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
	Console   _console;
	GitClient _git;

	TypeActive          _type {};
	std::tstring_t      _name;

	bool_t isError(std::ctstring_t &out, std::ctstring_t &stderr_str) const;
		///< Check if errors detected

	void_t traceOptions() const;
		///< trace options (configs)
	void_t traceColor(Console::Foreground color, std::ctstring_t &msg) const;
		///< trace using color
	void_t trace(std::ctstring_t &msg) const;
		///< trace obly
	void_t traceOk(std::ctstring_t &msg) const;
		///< trace as OK
	void_t traceError(std::ctstring_t &msg) const;
		///< trace as error
};

} // namespace xa
//-------------------------------------------------------------------------------------------------
