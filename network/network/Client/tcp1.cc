#include "client.ih"

Client Client::Tcp(string const &host, string const &port) 
{
	return resolve<Client>(AddressInfo::Tcp(host, port));
}
