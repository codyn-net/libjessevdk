#include "addressinfo.ih"

addrinfo AddressInfo::hint(int socktype, int protocol, int flags) 
{
	struct addrinfo hint;

	memset(&hint, 0, sizeof(hint));
	
	hint.ai_flags = flags;
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = socktype;
	hint.ai_protocol = protocol;
	
	return hint;
}
