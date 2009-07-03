#include "filedescriptor.ih"

FileDescriptor::Data::~Data() 
{
	close();
}
