#include "addressinfo.ih"

void AddressInfo::Split(string const &connection, string &protocol, string &host, string &port) 
{
	size_t pos = connection.find("://");
	String rest;

	if (pos != string::npos)
	{
		protocol = connection.substr(0, pos);
		rest = connection.substr(pos + 3);
	}
	else
	{
		protocol = "tcp";
		rest = connection;
	}
	
	vector<string> parts;
	
	if (rest.startsWith("::ffff:"))
	{
		parts = String(rest.substr(7)).split(":");
		parts[0] = string("::ffff:") + parts[0];
	}
	else
	{
		parts = rest.split(":");
	}
	
	if (parts.size() == 1)
	{
		if (!rest.empty() && rest.at(0) == ':')
			port = parts[0];
		else
			host = parts[0];
	}
	else
	{
		host = parts[0];
		port = parts[1];
	}
}
