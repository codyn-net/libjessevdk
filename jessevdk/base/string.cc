#include "string.hh"

using namespace std;
using namespace jessevdk::base;

bool
String::EndsWith(string const &other)
{
	size_t l = length();
	size_t ol = other.length();

	if (l < ol)
	{
		return false;
	}

	return substr(l - ol) == other;
}

String
String::Hex(char const *s, size_t num)
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

String
String::StripLeft() const
{
	size_t pos = find_first_not_of("\n\t ");

	if (pos != string::npos)
	{
		return substr(pos);
	}
	else
	{
		return *this;
	}
}

String::operator double () const
{
	return Convert<double>();
}

String
String::operator*(size_t num) const
{
	String ret;

	for (size_t i = 0; i < num; ++i)
	{
		ret += *this;
	}

	return ret;
}

String &
String::Replace(string const &search, string const &replace)
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

String
String::StripRight() const
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

vector<string>
String::Split(string const &delim, size_t mmax) const
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
			{
				result.push_back(part);
			}

			pos = size();
			break;
		}
		else
		{
			string part = substr(pos, next - pos);

			if (part != "" || result.size() == 0)
			{
				result.push_back(part);
			}

			pos = next + delim.size();
		}
	}

	if (result.size() == 0)
	{
		result.push_back("");
	}

	if (pos != size())
	{
		result[result.size() - 1] += substr(pos - 1);
	}

	return result;
}

bool
String::StartsWith(string const &other)
{
	return substr(0, other.length()) == other;
}

String
String::Strip() const
{
	return StripLeft().StripRight();
}
