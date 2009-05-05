#include "unixserver.ih"

AddressInfo UnixServer::listenAddressInfo() 
{
	return AddressInfo(d_data->filename);
}
