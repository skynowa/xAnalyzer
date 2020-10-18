/**
 * \file  Log.h
 * \brief
 */


#pragma once

#include "Config.h"

namespace xa
{
//-------------------------------------------------------------------------------------------------
class Log
    /// Analyzers logging
{
public:
///@name ctors, dtor
///@{
             Log();
             Log(std::tstring_t &title);
    virtual ~Log() = default;

    xNO_COPY_ASSIGN(Log)
///@}

    void_t write(std::ctstring_t &msg) const;
    void_t writeColor(Console::Foreground color, std::ctstring_t &msg) const;
    void_t writeOk(std::ctstring_t &msg) const;
    void_t writeError(std::ctstring_t &msg) const;

private:
	Console _console;

	std::ctstring_t _title;
};
//-------------------------------------------------------------------------------------------------
} // namespace xa
