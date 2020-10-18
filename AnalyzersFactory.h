/**
 * \file  AnalyzersFactory.h
 * \brief AnalyzersFactory
 */


#include <xLib/xLib.h>
#include "Config.h"
#include "Analyzers/IAnalyzer.h"
//-------------------------------------------------------------------------------------------------
namespace xa
{

class AnalyzerDataIn;

class AnalyzersFactory
{
public:
///@name ctors, dtor
///@{
	xNO_DEFAULT_CONSTRUCT(AnalyzersFactory)
	xNO_COPY_ASSIGN(AnalyzersFactory)
///@}

	static
	std::vector<IAnalyzer::Type> types();

	static
	const std::unique_ptr<IAnalyzer> &create(IAnalyzer::cType type, const AnalyzerDataIn &dataIn);

private:
	using analyzers_map_t = std::map<IAnalyzer::Type, std::unique_ptr<IAnalyzer>>;

	static analyzers_map_t _analyzers;
};

} // namespace xa
//-------------------------------------------------------------------------------------------------
