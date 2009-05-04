#include "filedescriptor.ih"

void FileDescriptor::assign(int fd)
{
	if (d_data->fd != -1)
		close();
	
	d_data->fd = fd;
	determineType();
}
