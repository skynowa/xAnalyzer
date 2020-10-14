/**
 * \file  Config.h
 * \brief config
 */


#pragma once

using namespace xl;

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
std::ctstring_t appName = xT("xAnalyzer");
//-------------------------------------------------------------------------------------------------
#if 0
""" Analyzer types """
TYPE_CPPCHECK        = 1
TYPE_CLANG_TIDY      = 2
TYPE_CLANG_TIDY_DIFF = 3
TYPE_ACTIVE          = TYPE_CLANG_TIDY

"" Check mode
0 - check changed files and headers
1 - check only changed files
""
QUICK_CHECK = 1

"" Set OS environment variable to disable checks
From shell: export ANALYZER_SKIP_CHECK=1

0 - enable checks
1 - skip checks
""
# SKIP_CHECK = os.environ.get("ANALYZER_SKIP_CHECK")
SKIP_CHECK = "1"

"" Disallow committing when errors/warnings occur
0 - allow commit
1 - disallow commit
""
STOP_ON_FAIL = 0

"" C++ language / standart ""
CPP_LANG = "c++"
CPP_STD  = "c++11"

""
Exclude files for checking
""
CPP_MASK = {".h", ".hh", ".hpp", ".inl", ".cc", ".cpp", ".cxx"}

"" Cppcheck ""
CPPCHECK_ERROR_LEVEL = "warning,missingInclude"
#else
// Analyzer types
enum class TypeActive
{
	TYPE_CPPCHECK        = 1,
	TYPE_CLANG_TIDY      = 2,
	TYPE_CLANG_TIDY_DIFF = 3,
	TYPE_ACTIVE          = TYPE_CLANG_TIDY
};

// Check mode
// 0 - check changed files and headers
// 1 - check only changed files

cbool_t QUICK_CHECK = true;

// Set OS environment variable to disable checks
// From shell: export ANALYZER_SKIP_CHECK=1
//
// 0 - enable checks
// 1 - skip checks

// SKIP_CHECK = os.environ.get("ANALYZER_SKIP_CHECK")
cbool_t SKIP_CHECK = true;

// Disallow committing when errors/warnings occur
// 0 - allow commit
// 1 - disallow commit

cbool_t STOP_ON_FAIL = false;

// C++ language / standart
std::ctstring_t CPP_LANG = "c++";
std::ctstring_t CPP_STD  = "c++11";

// Exclude files for checking
std::cvec_tstring_t CPP_MASK = {".h", ".hh", ".hpp", ".inl", ".cc", ".cpp", ".cxx"};

// Cppcheck
std::ctstring_t CPPCHECK_ERROR_LEVEL = "warning,missingInclude";

// Compiler types
enum class CompilerId
{
	COMPILER_ID_UNKNOWN = 0,
	COMPILER_ID_CLANG   = 1,
	COMPILER_ID_GCC     = 2
};

// Etc
std::ctstring_t PROJECT_DIR = "~/Projects/xLib";
std::csize_t    JOBS_NUM    = 1;

#endif
//-------------------------------------------------------------------------------------------------
