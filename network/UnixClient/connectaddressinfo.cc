#include "unixclient.ih"

AddressInfo UnixClient::connectAddressInfo() 
{
	return AddressInfo(d_data->filename);
}
