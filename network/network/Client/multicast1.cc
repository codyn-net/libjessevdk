#include "client.ih"

Client Client::Multicast(string const &host, string const &port, size_t ttl) 
{
	Client ret = resolve(AddressInfo::Udp(host, port));
	
	if (ret)
	{
		char val = static_cast<char>(ttl);
		
		setsockopt(ret, IPPROTO_IP, IP_MULTICAST_TTL, &val, sizeof(val));
	}
}
