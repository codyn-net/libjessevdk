#include "unixserver.ih"

AddressInfo UnixServer::listenAddressInfo() 
{
	return AddressInfo::Unix(d_data->filename);
}
