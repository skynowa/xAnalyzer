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
Log::Log(
	std::ctstring_t &a_title
) :
	_title(a_title)
{
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

	_console.writeLine(a_color, Console::Background::Default,
		static_cast<int_t>(Console::Attribute::Bold), _title + " " + a_msg);
}
//-------------------------------------------------------------------------------------------------
void_t
Log::writeOk(
	std::ctstring_t &a_msg
) const
{
	xCHECK_DO(a_msg.empty(), return);

	writeColor(Console::Foreground::Yellow, _title);
	writeColor(Console::Foreground::Green, " " + a_msg);
}
//-------------------------------------------------------------------------------------------------
void_t
Log::writeError(
	std::ctstring_t &a_msg
) const
{
	xCHECK_DO(a_msg.empty(), return);

	writeColor(Console::Foreground::Red, _title + " " + a_msg);
}
//-------------------------------------------------------------------------------------------------

} // namespace xa
