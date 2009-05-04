#include "string.ih"
#include <iostream>

bool String::endsWith(string const &other) 
{
	size_t l = length();
	size_t ol = other.length();
	
	if (l < ol)
		return false;

	return substr(l - ol) == other;
}
