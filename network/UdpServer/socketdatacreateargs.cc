#include "udpserver.ih"

Cloneable<FileDescriptor::DataArgs> UdpServer::Socket::Data::createArgs(int fd, string *buffer) 
{
	return UdpServer::DataArgs(fd, buffer, address);
}
