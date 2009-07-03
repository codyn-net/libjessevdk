#include "filedescriptor.ih"

FileDescriptor::FileDescriptor(bool createData)
{
	d_data = 0;
	
	if (!createData)
		return;
	
	d_data = new Data();
	addPrivateData(d_data);
	
	d_data->fd = -1;
}
