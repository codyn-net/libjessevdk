#include "client.ih"

Client Client::Multicast(string const &host, size_t port) 
{
	stringstream s;
	
	s << port;
	
	return Multicast(host, s.str());
}
