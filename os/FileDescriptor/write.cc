#include "filedescriptor.ih"

void FileDescriptor::write(string const &data)
{
	d_data->writeAll(data);
}
