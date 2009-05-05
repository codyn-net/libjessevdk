#include "tcpclient.ih"

AddressInfo TcpClient::connectAddressInfo() 
{
	return AddressInfo(d_data->host, d_data->port);
}
