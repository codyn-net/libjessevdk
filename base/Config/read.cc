#include "config.ih"

void Config::read(std::string const &filename)
{
	ifstream ifstr(filename.c_str());
	string line;

	while (getline(ifstr, line))
	{
		vector<string> parts = String(line).replace("\n", "").split("=", 2);

		if (parts.size() != 2)
		{
			parts.push_back("yes");
		}

		string key = String(parts[0]).strip();
		string value = String(parts[1]).strip();
		
		if (String(key).startsWith("#") || key == "")
		{
			continue;
		}

		if (!hasProperty(key))
		{
			cerr << "Invalid configuration option: " << key << endl;
		}

		PropertyBase &prop = property(key);

		if (!prop.serializable())
		{
			continue;
		}

		try
		{
			prop = value;
		}
		catch (exception e)
		{
			cerr << "Could not set config value `" << key << "' bad value: " << value << endl; 
		}
	}
}
