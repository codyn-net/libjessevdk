#include "client.ih"

Client Client::Multicast(string const &host, size_t port, size_t ttl) 
{
	stringstream s;
	
	s << port;
	
	return Multicast(host, s.str(), ttl);
}
