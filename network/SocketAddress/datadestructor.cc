#include "socketaddress.ih"

SocketAddress::Data::~Data()
{
	if (address)
		free(address);
}
