#include "string.ih"

String String::hex(char const *s, size_t num)
{
	stringstream st;
	
	char h[] = {'0', '1', '2', '3', '4', '5', '6', '7',
	            '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

	for (size_t i = 0; i < num; ++i)
	{
		st << h[(s[i] >> 4) & 0x0F] << h[s[i] & 0x0F];
	}
	
	return st.str();
}
