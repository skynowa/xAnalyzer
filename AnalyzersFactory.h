/**
 * \file  AnalyzersFactory.h
 * \brief AnalyzersFactory
 */


#include <xLib/xLib.h>
#include "Config.h"
//-------------------------------------------------------------------------------------------------
namespace xa
{

class IAnalyzer;

class AnalyzersFactory
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
	xNO_DEFAULT_CONSTRUCT(AnalyzersFactory)
	xNO_COPY_ASSIGN(AnalyzersFactory)
///@}

	static
	const std::unique_ptr<IAnalyzer> &create(cType type);

private:
	using analyzers_map_t = std::map<Type, std::unique_ptr<IAnalyzer>>;

	static analyzers_map_t _analyzers;
};

} // namespace xa
//-------------------------------------------------------------------------------------------------
