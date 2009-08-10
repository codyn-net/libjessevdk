#include "unixserver.ih"

void UnixServer::set(string const &filename) 
{
	d_data->filename = filename;
}
