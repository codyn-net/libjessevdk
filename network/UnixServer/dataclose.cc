#include "unixserver.ih"

void UnixServer::Data::close() 
{
	Server::Data::close();
	
	::unlink(filename.c_str());
}
