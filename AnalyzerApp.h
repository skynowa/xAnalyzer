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

	SystemInfo::OsType  _os_name {};
	TypeActive          _type {};
	std::tstring_t      _name;
	std::vec_tstring_t  _git_modified_files;
	std::tstring_t      _complier_id;
	std::tstring_t      _complier_name;
	std::tstring_t      _include_dirs;

	void_t getComplierInfo(::CompilerId *complier_id, std::tstring_t *complier_name) const;
		///< get complier info (ID, name)
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
