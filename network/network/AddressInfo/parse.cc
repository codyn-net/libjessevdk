#include "addressinfo.ih"

AddressInfo AddressInfo::Parse(string const &connection) 
{
	string protocol;
	string host = "";
	string port = "";
	
	Split(connection, protocol, host, port);

	if (host == "" && port == "")
		return AddressInfo();

	if (protocol == "unix")
	{
		return AddressInfo::Unix(port != "" ? port : host);
	}
	else if (protocol == "tcp")
	{
		return AddressInfo::Tcp(host, port);
	}
	else if (protocol == "udp")
	{
		return AddressInfo::Udp(host, port);
	}
	
	return AddressInfo();
}
