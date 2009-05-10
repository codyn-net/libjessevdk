#include "addressinfo.ih"

AddressInfo AddressInfo::Udp(string const &port) 
{
	return Udp("", port);
}
