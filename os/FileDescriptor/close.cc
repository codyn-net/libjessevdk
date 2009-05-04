#include "filedescriptor.ih"

void FileDescriptor::close()
{
	d_data->close();
}
