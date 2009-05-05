#include "unixserver.ih"

void UnixServer::close() 
{
	Server::close();
	
	::unlink(d_data->filename.c_str());
}
