#include "addressinfo.ih"

AddressInfo AddressInfo::Tcp(string const &host, string const &port) 
{
	return resolve(host, port, hint(SOCK_STREAM, IPPROTO_TCP));	
}
