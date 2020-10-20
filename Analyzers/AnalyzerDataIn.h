/**
 * \file  AnalyzerDataIn.h
 * \brief Analyzers incoming data
 */


#pragma once

#include "../Config.h"

namespace xa
{
//-------------------------------------------------------------------------------------------------
class AnalyzerDataIn :
	public IData
{
public:
	enum class CompilerId
	{
		Unknown = 0,
		Clang   = 1,
		Gcc     = 2
	};
	xUSING_CONST(CompilerId);

	// common
	std::tstring_t     projectDirPath;
	std::tstring_t     cppLanguage;
	std::tstring_t     cppStandart;
	std::vec_tstring_t includeDirs;
	std::vec_tstring_t modifiedFiles;
	std::tstring_t     defines;			// TODO: impl
	SystemInfo::OsType osName {};		// includeDirs
	CompilerId         compilerId {};	// ClangTidy
	std::tstring_t     compilerName;	//
	bool_t             isSkipCheck {};
	bool_t             isStopOnFail {};
	bool_t             isQuickCheck {};	// ClangTidy

	// partial - CppCheck
	std::tstring_t     cppCheck_cLanguage;
	std::size_t        cppCheck_jobsNum {};
	std::tstring_t     cppCheck_errorLevel;

///@name ctors, dtor
///@{
	 AnalyzerDataIn();
	~AnalyzerDataIn() = default;
///@}

	bool_t isValid() const override;
	void_t clear() override;
	void_t print(core::OStream &os) const override;

private:
	void_t _complierInfo(CompilerId *complier_id, std::tstring_t *complier_name) const;
		///< get complier info (ID, name)
	void_t _includeDirs(std::vec_tstring_t *dirPathes) const;
		///< get include dirs
	void_t _compilerIncludeDirs(std::vec_tstring_t *dirPathes) const;
		///< get compiler include dirs
	void_t _pkgConfig(std::ctstring_t &lib_name, std::vec_tstring_t *cflags) const;
		///< get libs, cflags by pkg-config tool
};
xUSING_CONST(AnalyzerDataIn);
//-------------------------------------------------------------------------------------------------
} // namespace xa
