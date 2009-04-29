#include "string.ih"

bool String::startsWith(string const &other) 
{
	return other.substr(0, other.length()) == other;
}
