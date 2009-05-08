#include "client.ih"

Client Client::Tcp(string const &host, size_t port) 
{
	stringstream istr;
	
	istr << port;
	return Tcp(host, istr.str());
}
