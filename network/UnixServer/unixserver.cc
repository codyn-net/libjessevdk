#include "unixserver.ih"

UnixServer::UnixServer(string const &filename) 
{
	d_data = new Data();
	addPrivateData(d_data);
	
	d_data->filename = filename;
}
