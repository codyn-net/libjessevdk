#include "client.ih"

Client Client::Udp(string const &host, size_t port) 
{
	stringstream istr;
	
	istr << port;
	return Udp(host, istr.str());
}
