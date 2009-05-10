#include "client.ih"

Client Client::Udp(string const &host, string const &port) 
{
	Client cl = resolve(AddressInfo::Udp(host, port));
	cl.detach();
	
	return cl;
}
