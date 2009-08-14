#include "string.ih"

String &String::replace(string const &search, string const &replace) 
{
	size_type lastpos = 0;

	while (true)
	{
		size_type s = find(search, lastpos);
		
		if (s == string::npos)
			break;
		
		string::replace(s, search.length(), replace);
		lastpos = s + replace.length();
	}

	return *this;
}
