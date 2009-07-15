#include "udpserver.ih"

UdpServer::Socket *UdpServer::Socket::clone() const
{
	return new Socket(*this);
}
