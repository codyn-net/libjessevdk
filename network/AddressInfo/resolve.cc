#include "addressinfo.ih"

AddressInfo AddressInfo::resolve(std::string const &host, std::string const &port, struct addrinfo hint)
{
	struct addrinfo *addr;

	if (host == "")
		hint.ai_flags |= AI_PASSIVE;

	int ret = getaddrinfo(host == "" ? 0 : host.c_str(), port.c_str(), &hint, &addr);
	return AddressInfo(ret, addr);
}
