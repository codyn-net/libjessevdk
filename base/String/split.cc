#include "string.ih"

vector<string> String::split(string const &delim, size_t mmax) const
{
	vector<string> result;
	string::size_type pos = 0;
	
	while (mmax == 0 || result.size() < mmax)
	{
		string::size_type next = find(delim, pos);
		
		if (next == string::npos)
		{
			string part = substr(pos, size() - pos);
			
			if (part != "")
				result.push_back(part);
			
			pos = size();
			break;
		}
		else
		{
			string part = substr(pos, next - pos);

			if (part != "" || result.size() == 0)
				result.push_back(part);

			pos = next + delim.size();
		}
	}
	
	if (result.size() == 0)
		result.push_back("");

	if (pos != size())
		result[result.size() - 1] += substr(pos - 1);
	
	return result;
}
