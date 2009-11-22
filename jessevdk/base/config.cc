#include "config.hh"

#include <fstream>

using namespace jessevdk::base;
using namespace std;

Config::Config()
:
	Object(),
	Properties(dynamic_cast<Object &>(*this))
{
}

void
Config::Read(std::string const &filename)
{
	ifstream ifstr(filename.c_str());
	string line;

	while (getline(ifstr, line))
	{
		vector<string> parts = String(line).Replace("\n", "").Split("=", 2);

		if (parts.size() != 2)
		{
			parts.push_back("yes");
		}

		string key = String(parts[0]).Strip();
		string value = String(parts[1]).Strip();

		if (String(key).StartsWith("#") || key == "")
		{
			continue;
		}

		if (!HasProperty(key))
		{
			cerr << "Invalid configuration option: " << key << endl;
		}

		properties::PropertyBase &prop = GetProperty(key);

		if (!prop.Serializable())
		{
			continue;
		}

		try
		{
			prop = value;
		}
		catch (exception &e)
		{
			cerr << "Could not set config value `" << key << "' bad value: " << value << endl;
		}
	}
}
