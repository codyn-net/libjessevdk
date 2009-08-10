#include "server.ih"

Cloneable<Socket> Server::socketFromInfo(AddressInfo &info) 
{
	return Socket(info);
}
