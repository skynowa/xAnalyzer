/**
 * \file  AnalyzerFactory.cpp
 * \brief AnalyzerFactory
 */


#include "AnalyzerFactory.h"

#include "Analyzers/CppCheck.h"
#include "Analyzers/ClangTidy.h"

namespace xa
{

//-------------------------------------------------------------------------------------------------
AnalyzerFactory::analyzers_map_t AnalyzerFactory::_analyzers;
//-------------------------------------------------------------------------------------------------
/* static */
const std::unique_ptr<IAnalyzer> &
AnalyzerFactory::create(
	cType a_type
)
{
	if (auto it = _analyzers.find(a_type); it != _analyzers.cend()) {
		return it->second;
	}

	switch (a_type) {
	case Type::CppCheck:
		_analyzers[a_type] = std::make_unique<CppCheck>();
		break;
	case Type::ClangTidy:
		_analyzers[a_type] = std::make_unique<ClangTidy>();
		break;
	}

	xTEST_GR(_analyzers.count(a_type), std::size_t{0});

	return _analyzers[a_type];
}
//-------------------------------------------------------------------------------------------------

} // namespace xa