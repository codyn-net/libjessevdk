#include "tcpconnection.ih"

Connection::Connection()
{
	d_data = new Data();
	addPrivateData(d_data);
}
