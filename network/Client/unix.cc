#include "client.ih"

Client Client::Unix(string const &filename) 
{
	return resolve(AddressInfo(filename));
}
