/**
 * \file  IAnalyzer.h
 * \brief Analyzers interface
 */


#pragma once

#include "../Config.h"
#include "../Log.h"
#include "AnalyzerDataIn.h"
#include "AnalyzerDataOut.h"

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

    virtual bool_t run(AnalyzerDataOut *dataOut) = 0;

protected:
	virtual void_t _parseReport(AnalyzerDataOut *dataOut) const = 0;
		///< out data,parse
	virtual bool_t _isError(const AnalyzerDataOut &dataOut) const = 0;
		///< out data, check if errors detected

protected:
	cType           _type {};
	std::tstring_t  _name;
	cAnalyzerDataIn _dataIn;

	std::tstring_t  _binPath() const;
		///< path to binary file
};
//-------------------------------------------------------------------------------------------------
} // namespace xa
