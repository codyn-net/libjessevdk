#include "client.ih"

Client Client::Unix(string const &filename) 
{
	return Client::connect(AddressInfo(filename));
}
