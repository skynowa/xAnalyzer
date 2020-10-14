/**
 * \file  ClangTidy.cpp
 * \brief ClangTidy
 */


#include "ClangTidy.h"


namespace xa
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
ClangTidy::ClangTidy()
{
}
//-------------------------------------------------------------------------------------------------
ClangTidy::~ClangTidy()
{
}
//-------------------------------------------------------------------------------------------------
void_t
ClangTidy::run() /* override */
{
#if 0
def runClangTidy(self):
	"" Run analysis by Clang-Tidy ""

	line_filter = "" # n/a

	args_stdlib = {
		self.COMPILER_ID_CLANG: "-stdlib=libstdc++",
		self.COMPILER_ID_GCC:   ""
	}

	force_cpp = "-x " + options.CPP_LANG

	header_filter = ""
	if (options.QUICK_CHECK == 1):
		header_filter = "" # skip
	else:
		header_filter = "^{}/.*".format(self.PROJECT_DIR) # all

	cmd = \
		"clang-tidy " \
		"{} " \
		"-system-headers=0 " \
		"-line-filter={} " \
		"-header-filter={} " \
		"-extra-arg=-std={} " \
		"-extra-arg={} " \
		"-quiet " \
		"-- " \
		"{} " \
		"{}" \
		.format(self._git_modified_files, line_filter, header_filter,
			options.CPP_STD, args_stdlib[self._complier_id], self._include_dirs,
			force_cpp) \
		.split()
	print("cmd: ", cmd)

	return subprocess.Popen(cmd, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
#else

#endif
}
//-------------------------------------------------------------------------------------------------
void_t
ClangTidy::runDiff() const
{
#if 0
def runClangTidyDiff(self):
	"" Run analysis by Clang-Tidy-Diff ""

	line_filter = self.getGitModifiedFilesLineFilter()

	args_stdlib = {
		self.COMPILER_ID_CLANG: "-stdlib=libstdc++",
		self.COMPILER_ID_GCC:   ""
	}

	force_cpp = "-x " + options.CPP_LANG

	header_filter = ""
	if (options.QUICK_CHECK == 1):
		header_filter = "" # skip
	else:
		header_filter = "^{}/.*".format(self.PROJECT_DIR) # all

	cmd = \
		"clang-tidy " \
		"{} " \
		"-system-headers=0 " \
		"-line-filter={} " \
		"-header-filter={} " \
		"-extra-arg=-std={} " \
		"-extra-arg={} " \
		"-quiet " \
		"-- " \
		"{} " \
		"{}" \
		.format(self._git_modified_files, line_filter, header_filter,
			options.CPP_STD, args_stdlib[self._complier_id], self._include_dirs,
			force_cpp) \
		.split()
	print("cmd: ", cmd)

	return subprocess.Popen(cmd, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
#else

#endif
}
//-------------------------------------------------------------------------------------------------
void_t
ClangTidy::runFile() const
{
#if 0
def runClangTidyFile(self):
	"" Run analysis by Clang-Tidy-File ""

	args_stdlib = {
		self.COMPILER_ID_CLANG: "-stdlib=libstdc++",
		self.COMPILER_ID_GCC:   ""
	}

	force_cpp = "-x " + options.CPP_LANG

	header_filter = ""
	if (options.QUICK_CHECK == 1):
		header_filter = "" # skip
	else:
		header_filter = "^{}/.*".format(self.PROJECT_DIR) # all

	cmd = \
		"clang-tidy " \
		"{} " \
		"-system-headers=0 " \
		"-header-filter={} " \
		"-extra-arg=-std={} " \
		"-extra-arg={} " \
		"-quiet " \
		"-- " \
		"{} " \
		"{}" \
		.format(self._file_to_check, header_filter,
			options.CPP_STD, args_stdlib[self._complier_id], self._include_dirs,
			force_cpp) \
		.split()
	print("cmd: ", cmd)

	return subprocess.Popen(cmd, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
#else

#endif
}
//-------------------------------------------------------------------------------------------------

} // namespace xa
