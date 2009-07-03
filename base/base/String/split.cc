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
			string part = substr(pos, size() - pos);
			
			if (part != "")
				result.push_back(part);
			break;
		}
		else
		{
			string part = substr(pos, next - pos);

			if (part != "")
				result.push_back(part);

			pos = next + delim.size();
		}
	}
	
	if (result.size() == 0)
		result.push_back("");
	
	return result;
}
