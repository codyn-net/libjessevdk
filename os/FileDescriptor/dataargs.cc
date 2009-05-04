#include "filedescriptor.ih"

FileDescriptor::DataArgs::DataArgs(int fd, string *buffer)
:
	fd(fd),
	privBuffer(buffer)
{
	data = *buffer;
}
