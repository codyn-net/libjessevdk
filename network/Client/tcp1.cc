#include "client.ih"

Client Client::Tcp(string const &host, string const &port) 
{
	return connect(AddressInfo(host, port));
}
