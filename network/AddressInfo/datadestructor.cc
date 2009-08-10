#include "addressinfo.ih"

AddressInfo::Data::~Data() 
{
	if (address)
	{
		if (freeAddress)
		{
			delete address->ai_addr;
		}
		
		freeaddrinfo(address);
	}
}
