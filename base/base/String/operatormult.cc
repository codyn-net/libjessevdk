#include "string.ih"

String String::operator*(size_t num) const
{
	String ret;
	
	for (size_t i = 0; i < num; ++i)
	{
		ret += *this;
	}
	
	return ret;
}
