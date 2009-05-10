#include "addressinfo.ih"

AddressInfo AddressInfo::Udp(string const &host, string const &port) 
{
	return resolve(host, port, hint(SOCK_DGRAM, IPPROTO_UDP));	
}
