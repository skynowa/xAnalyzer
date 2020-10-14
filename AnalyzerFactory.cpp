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
std::unique_ptr<IAnalyzer>
AnalyzerFactory::create(
	cType a_type
)
{
	auto it = _analyzers.find(a_type);
	if (it != _analyzers.cend()) {
		return it->second;
	}

	std::unique_ptr<Type> analyzer;

	switch (a_type) {
	case Type::CppCheck:
		analyzer = std::unique_ptr<IAnalyzer>(new CppCheck());
		break;
	case Type::ClangTidy:
		analyzer = std::unique_ptr<IAnalyzer>(new ClangTidy());
		break;
	}

	_analyzers[a_type] = analyzer;

	return analyzer;
}
//-------------------------------------------------------------------------------------------------

} // namespace xa
