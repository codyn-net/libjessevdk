#include "filedescriptor.ih"

Cloneable<FileDescriptor::DataArgs> FileDescriptor::Data::createArgs(int fd, string *buffer) 
{
	return DataArgs(fd, buffer);
}
