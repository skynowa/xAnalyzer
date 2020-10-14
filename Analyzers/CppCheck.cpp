/**
 * \file  CppCheck.cpp
 * \brief CppCheck
 */


#include "CppCheck.h"


namespace xa
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
CppCheck::CppCheck()
{
}
//-------------------------------------------------------------------------------------------------
CppCheck::~CppCheck()
{
}
//-------------------------------------------------------------------------------------------------
void_t
CppCheck::run() /* override */
{
#if 0
def runCppcheck(self):
	"" Run analysis Cppcheck ""

	cmd = \
		"cppcheck " \
		"{} {} " \
		"--library=std.cfg --library=posix.cfg " \
		"-UKERN_PROC_PATHNAME " \
		"--enable={} --inconclusive " \
		"--language=c --language={} --std={} " \
		"--platform=unix64 " \
		"--force " \
		"-j{} " \
		"--relative-paths " \
		"--error-exitcode=1" \
		.format(self._include_dirs, self._git_modified_files, options.CPPCHECK_ERROR_LEVEL,
			options.CPP_LANG, options.CPP_STD, self.JOBS_NUM) \
		.split()
	print("cmd: ", cmd)

	return subprocess.Popen(cmd, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
#else
	std::ctstring_t include_dirs       = "self._include_dirs";
	std::ctstring_t git_modified_files = "self._git_modified_files";

	std::cvec_tstring_t params
	{
		include_dirs,
		git_modified_files,
		"--library=std.cfg", "--library=posix.cfg",
		/// "-UKERN_PROC_PATHNAME",
		"--enable=" + ::CPPCHECK_ERROR_LEVEL, "--inconclusive",
		"--language=c", "--language=" + ::CPP_LANG, "--std=" + ::CPP_STD,
		"--platform=unix64",
		"--force ",
		"-j" + std::to_string(::JOBS_NUM),
		"--relative-paths",
		"--error-exitcode=1"
	};

	std::tstring_t stdOut;
	std::tstring_t stdError;

	Process::execute("cppcheck", params, {}, xTIMEOUT_INFINITE, &stdOut, &stdError);
#endif
}
//-------------------------------------------------------------------------------------------------

} // namespace xa
