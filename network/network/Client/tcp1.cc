#include "client.ih"

Client Client::Tcp(string const &host, string const &port) 
{
	return resolve(AddressInfo::Tcp(host, port));
}
