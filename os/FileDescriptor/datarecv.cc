#include "filedescriptor.ih"

int FileDescriptor::Data::recv(string &data) 
{
	char buffer[1024];
	ssize_t len;
	
	len = this->read(buffer, 1024 - 1);
	
	if (len >= 0)
		buffer[len] = '\0';

	data = buffer;	
	return len;
}
