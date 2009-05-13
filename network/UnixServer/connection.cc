#include "unixserver.ih"

string UnixServer::connection()
{
	return string("unix://:") + d_data->filename;
}
