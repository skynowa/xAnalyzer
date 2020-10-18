/**
 * \file  IAnalyzer.h
 * \brief Analyzers interface
 */


#pragma once

#include "../Config.h"
#include "AnalyzerDataIn.h"

namespace xa
{
//-------------------------------------------------------------------------------------------------
class IAnalyzer
    /// Analyzers interface
{
public:
	/**
	 * Analyzer types
	 */
	enum class Type
	{
		CppCheck  = 1,
		ClangTidy = 2
	};
	xUSING_CONST(Type);

///@name ctors, dtor
///@{
             IAnalyzer(cType type, cAnalyzerDataIn &dataIn);
    virtual ~IAnalyzer() = default;

    xNO_COPY_ASSIGN(IAnalyzer)
///@}

    virtual void_t run() = 0;

protected:
	cType           _type {};
	std::tstring_t  _name;
	cAnalyzerDataIn _dataIn;

	std::tstring_t  _binPath() const;
		///< path to binary file
	virtual void_t  _parseReport(std::ctstring_t &stdOut, std::ctstring_t &stdError) const = 0;
		///<
};
//-------------------------------------------------------------------------------------------------
} // namespace xa
