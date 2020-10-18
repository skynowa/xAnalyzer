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

	SystemInfo::OsType  _os_name {};
	TypeActive          _type {};
	std::tstring_t      _name;
	std::vec_tstring_t  _git_modified_files;
	std::vec_tstring_t  _include_dirs;

	void_t complierInfo(::CompilerId *complier_id, std::tstring_t *complier_name) const;
		///< get complier info (ID, name)
	void_t includeDirs(std::vec_tstring_t *dirPathes) const;
		///< get include dirs
	void_t compilerIncludeDirs(std::vec_tstring_t *dirPathes) const;
		///< get compiler include dirs
	void_t pkgConfig(std::ctstring_t &lib_name, std::vec_tstring_t *cflags) const;
		///< get libs, cflags by pkg-config tool

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
