#include "client.ih"

Client Client::Udp(string const &host, string const &port) 
{
	struct addrinfo hint;
	
	memset(&hint, 0, sizeof(hint));
	
	hint.ai_flags = 0;
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_DGRAM;
	hint.ai_protocol = IPPROTO_UDP;

	return resolve(AddressInfo(host, port, hint));
}
