#include "filedescriptor.ih"

ssize_t FileDescriptor::Data::write(char const *buffer, ssize_t len) 
{
	return ::write(fd, buffer, len);
}
