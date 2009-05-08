#include "filedescriptor.ih"

ssize_t FileDescriptor::Data::read(char *buffer, ssize_t len)
{
	return ::read(fd, buffer, len);
}
