#include "string.ih"

bool String::endsWith(string const &other) 
{
	size_t l = length();
	size_t ol = other.length();
	
	if (l < ol)
		return false;

	return other.substr(l - ol) == other;
}
