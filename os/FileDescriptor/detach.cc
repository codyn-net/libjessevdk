#include "filedescriptor.ih"

void FileDescriptor::detach() 
{
	if (d_data->fd == -1)
		return;

	if (d_data->sourceConnection)
	{
		d_data->sourceConnection.disconnect();
	}
}
