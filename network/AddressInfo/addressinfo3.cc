#include "addressinfo.ih"

AddressInfo::AddressInfo(int ret, struct addrinfo *addr)
{
	initialize(ret, addr);
}
