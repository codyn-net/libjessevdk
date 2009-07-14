#include "string.ih"
#include <iostream>

String String::lstrip() const
{
	size_t pos = find_first_not_of("\n\t ");
	
	if (pos != string::npos)
	{
		return substr(pos);
	}
	else
	{
		return *this;
	}
}
