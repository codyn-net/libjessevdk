#include "addressinfo.ih"

bool AddressInfo::isIPAddress(string const &host)
{
	return String(host).split(".").size() == 4;
}
