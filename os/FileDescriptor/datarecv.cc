#include "filedescriptor.ih"

int FileDescriptor::Data::recv(string &data) 
{
	char buffer[1024];
	ssize_t len;
	
	if (type == Type::Socket)
	{
		len = ::recv(fd, buffer, 1024 - 1, 0);
	}
	else
	{
		len = ::read(fd, buffer, 1024 - 1);
	}
	
	if (len >= 0)
		buffer[len] = '\0';

	data = buffer;	
	return len;
}
