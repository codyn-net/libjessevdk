#include "filedescriptor.ih"

void FileDescriptor::setData(Data *data) 
{
	d_data = data;
	d_data->fd = -1;
}
