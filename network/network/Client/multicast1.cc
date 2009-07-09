#include "client.ih"

Client Client::Multicast(string const &host, string const &port) 
{
	return resolve(AddressInfo::Udp(host, port));
}
