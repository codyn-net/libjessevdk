#include "string.ih"

vector<string> String::split(string const &delim) const
{
	vector<string> result;
	string::size_type pos = 0;
	
	while (true)
	{
		string::size_type next = find(delim, pos);
		
		if (next == string::npos)
		{
			result.push_back(substr(pos, size() - pos));
			break;
		}
		else
		{
			result.push_back(substr(pos, next - pos));
			pos = next + delim.size();
		}
	}
	
	return result;
}
