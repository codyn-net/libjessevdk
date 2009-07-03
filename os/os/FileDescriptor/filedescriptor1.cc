#include "filedescriptor.ih"

FileDescriptor::FileDescriptor(int fd)
{
	d_data = new Data();
	addPrivateData(d_data);
	
	d_data->fd = -1;
	assign(fd);
}
