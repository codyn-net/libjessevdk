#include "unixserver.ih"

bool UnixServer::listenOnSocket(Socket &socket) 
{
	return socket.listen(20);
}
