#include "client.ih"

Client Client::Unix(string const &filename) 
{
	return resolve<Client>(AddressInfo::Unix(filename));
}
