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
	GitClient _git;

	void_t getComplierInfo() const;
	void_t getIncludeDirs() const;
	void_t getCompilerIncludeDirs() const;
	void_t getPkgConfig(std::ctstring_t &lib_name) const;

	bool_t isError(std::ctstring_t &out, std::ctstring_t &stderr_str) const;
	void_t traceOptions() const;
		///< Trace options (configs)
	void_t traceColor(std::ctstring_t &color, std::ctstring_t &msg) const;
	void_t trace(std::ctstring_t &msg) const;
	void_t traceOk(std::ctstring_t &msg) const;
	void_t traceError(std::ctstring_t &msg) const;
};

} // namespace xa
//-------------------------------------------------------------------------------------------------
/**
 * TODO:
 *
 * - Go to source line into editor
 */
//-------------------------------------------------------------------------------------------------
