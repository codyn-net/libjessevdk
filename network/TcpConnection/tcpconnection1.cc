#include "tcpconnection.ih"

TcpConnection::TcpConnection()
{
	d_data = new Data();
	addPrivateData(&d_data);
}
