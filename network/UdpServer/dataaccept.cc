#include "udpserver.ih"

Socket UdpServer::Data::accept() 
{
	/* Cannot accept */
	return Socket();
}
