#include "addressinfo.ih"

void AddressInfo::resolve(std::string const &host, std::string const &port, struct addrinfo hint)
{
	struct addrinfo *addr;
	int ret = getaddrinfo(host.c_str(), port.c_str(), &hint, &addr);
	
	initialize(ret, addr);
}
