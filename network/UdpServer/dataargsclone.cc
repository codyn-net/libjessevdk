#include "udpserver.ih"

UdpServer::DataArgs *UdpServer::DataArgs::clone() const
{
	return new DataArgs(*this);
}
