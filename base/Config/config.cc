#include "config.ih"

Config::Config()
:
	Object(),
	Properties(dynamic_cast<Object &>(*this))
{
}
