#include "addressinfo.ih"

bool AddressInfo::isMulticast(string const &host)
{
	size_t pos = host.find(".");
	
	if (pos == string::npos)
		return false;
	
	stringstream s;
	s << host.substr(0, pos);
	size_t part = 0;
	
	s >> part;
	
	return (part >= 224 && part <= 239);
}
