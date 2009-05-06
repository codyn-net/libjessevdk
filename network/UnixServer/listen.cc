#include "unixserver.ih"

bool UnixServer::listen() 
{
	::unlink(d_data->filename.c_str());
	return Server::listen();
}
