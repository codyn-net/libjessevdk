#include "udpserver.ih"

UdpServer::DataArgs::DataArgs(int fd, string *buffer, SocketAddress &address) 
:
	FileDescriptor::DataArgs(fd, buffer),
	address(address)
{
}
