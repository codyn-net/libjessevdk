#include "addressinfo.ih"

AddressInfo::Data::~Data() 
{
	if (address)
		freeaddrinfo(address);
}
