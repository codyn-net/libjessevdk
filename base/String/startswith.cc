#include "string.ih"

bool String::startsWith(string const &other) 
{
	return substr(0, other.length()) == other;
}
