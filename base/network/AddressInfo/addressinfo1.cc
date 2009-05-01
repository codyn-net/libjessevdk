#include "addressinfo.ih"

AddressInfo::AddressInfo(string const &host, string const &name, struct addrinfo hint)
{
	resolve(host, name, hint);
}
