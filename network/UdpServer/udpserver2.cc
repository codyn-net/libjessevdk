#include "udpserver.ih"

UdpServer::UdpServer(string const &port) 
{
	initialize("localhost", port);
}
