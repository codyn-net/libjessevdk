#include "string.ih"

String String::rstrip() const
{
	size_t pos = find_last_not_of("\n\t ");
	
	if (pos != string::npos && pos != 0)
	{
		return substr(0, pos + 1);
	}
	else
	{
		return *this;
	}
}
