#include "addressinfo.ih"

AddressInfo AddressInfo::Tcp(string const &port) 
{
	return Tcp("", port);
}
