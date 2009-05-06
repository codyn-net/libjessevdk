#include "unixserver.ih"

UnixServer::Data::~Data() 
{
	::unlink(filename.c_str());
}
