#include "addressinfo.ih"

AddressInfo::AddressInfo(string const &host, string const &name)
{
	struct addrinfo hint;

	memset(&hint, 0, sizeof(hint));
	
	hint.ai_flags = 0;
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = IPPROTO_TCP;
	
	resolve(host, name, hint);
}
