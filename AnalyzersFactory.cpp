/**
 * \file  AnalyzersFactory.cpp
 * \brief AnalyzersFactory
 */


#include "AnalyzersFactory.h"

#include "Analyzers/CppCheck.h"
#include "Analyzers/ClangTidy.h"

namespace xa
{

//-------------------------------------------------------------------------------------------------
AnalyzersFactory::analyzers_map_t AnalyzersFactory::_analyzers;
//-------------------------------------------------------------------------------------------------
/* static */
const std::unique_ptr<IAnalyzer> &
AnalyzersFactory::create(
	cType            a_type,
	cAnalyzerDataIn &a_dataIn
)
{
	if (auto it = _analyzers.find(a_type); it != _analyzers.cend()) {
		return it->second;
	}

	switch (a_type) {
	case Type::CppCheck:
		_analyzers[a_type] = std::make_unique<CppCheck>(a_dataIn);
		break;
	case Type::ClangTidy:
		_analyzers[a_type] = std::make_unique<ClangTidy>(a_dataIn);
		break;
	}

	xTEST_GR(_analyzers.count(a_type), std::size_t{0});

	return _analyzers[a_type];
}
//-------------------------------------------------------------------------------------------------

} // namespace xa
