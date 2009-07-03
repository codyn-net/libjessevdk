#include "udpserver.ih"

Cloneable<FileDescriptor::DataArgs> UdpServer::Data::createArgs(int fd, string *buffer) 
{
	return DataArgs(fd, buffer, address);
}
