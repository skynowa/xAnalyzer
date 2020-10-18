/**
 * \file  Log.h
 * \brief
 */


#include "Log.h"

namespace xa
{

//-------------------------------------------------------------------------------------------------
Log::Log()
{
	_console.setEscapeValues(false);
}
//-------------------------------------------------------------------------------------------------
void_t
Log::write(
	std::ctstring_t &a_msg
) const
{
	_console.writeLine(a_msg);
}
//-------------------------------------------------------------------------------------------------
void_t
Log::writeColor(
	Console::Foreground  a_color,
	std::ctstring_t     &a_msg
) const
{
	xCHECK_DO(a_msg.empty(), return);

#if 0
	_console.writeLine(a_color, Console::Background::Default,
		static_cast<int_t>(Console::Attribute::Bold), _name + " " + a_msg);
#endif
}
//-------------------------------------------------------------------------------------------------
void_t
Log::writeOk(
	std::ctstring_t &a_msg
) const
{
	xCHECK_DO(a_msg.empty(), return);

#if 0
	traceColor(Console::Foreground::Yellow, _name);
	traceColor(Console::Foreground::Green, " " + a_msg);
#endif
}
//-------------------------------------------------------------------------------------------------
void_t
Log::writeError(
	std::ctstring_t &a_msg
) const
{
	xCHECK_DO(a_msg.empty(), return);

#if 0
	_console.traceColor(Console::Foreground::Red, _name + " " + a_msg);
#endif
}
//-------------------------------------------------------------------------------------------------

} // namespace xa
