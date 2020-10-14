/**
 * \file  xAnalyzerApp.h
 * \brief xAnalyzerApp
 */


#include <xLib/xLib.h>
#include "Config.h"
//-------------------------------------------------------------------------------------------------
namespace xa
{

class xAnalyzerApp :
	public Application
{
public:
///@name ctors, dtor
///@{
	xAnalyzerApp(std::ctstring_t &appGuid, std::ctstring_t &locale);
	~xAnalyzerApp() = default;

	xNO_COPY_ASSIGN(xAnalyzerApp)
///@}

	ExitCode onRun() override;

private:
	void_t runCppcheck() const;
	void_t runClangTidy() const;
	void_t runClangTidyDiff() const;
	void_t runClangTidyFile() const;

	void_t getComplierInfo() const;
	void_t getIncludeDirs() const;
	void_t getCompilerIncludeDirs() const;
	void_t getPkgConfig(std::ctstring_t &lib_name) const;

	bool_t isError(std::ctstring_t &out, std::ctstring_t &stderr_str) const;
	void_t traceOptions() const;
	void_t traceColor(std::ctstring_t &color, std::ctstring_t &msg) const;
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
