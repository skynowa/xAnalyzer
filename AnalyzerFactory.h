/**
 * \file  AnalyzerFactory.h
 * \brief AnalyzerFactory
 */


#include <xLib/xLib.h>
#include "Config.h"
//-------------------------------------------------------------------------------------------------
namespace xa
{

class IAnalyzer;

class AnalyzerFactory
{
public:
	enum class Type
	{
		CppCheck  = 0,
		ClangTidy = 1
	};
	xUSING_CONST(Type);

///@name ctors, dtor
///@{
	AnalyzerFactory() = default;
   ~AnalyzerFactory() = default;

	xNO_COPY_ASSIGN(AnalyzerFactory)
///@}

	static
	std::unique_ptr<IAnalyzer> create(cType type);

private:
	static std::map<Type, std::unique_ptr<IAnalyzer>> _analyzers;
};

} // namespace xa
//-------------------------------------------------------------------------------------------------
