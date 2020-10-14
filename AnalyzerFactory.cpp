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
/* static */
std::unique_ptr<IAnalyzer> &
AnalyzerFactory::create(
	cType a_type
)
{
	if (auto it = _analyzers.find(a_type); it != _analyzers.cend()) {
		return it->second;
	}

	std::unique_ptr<IAnalyzer> analyzer;

	switch (a_type) {
	case Type::CppCheck:
		analyzer = std::make_unique<CppCheck>();
		break;
	case Type::ClangTidy:
		analyzer = std::make_unique<ClangTidy>();
		break;
	}

	_analyzers[a_type] = std::move(analyzer);

	return analyzer;
}
//-------------------------------------------------------------------------------------------------

} // namespace xa
