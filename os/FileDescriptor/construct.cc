#include "filedescriptor.ih"

void FileDescriptor::construct(int fd, Data *data)
{
	d_data = data;
	d_data->fd = fd;
	
	determineType();
}
