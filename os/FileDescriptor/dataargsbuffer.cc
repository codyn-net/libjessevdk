#include "filedescriptor.ih"

void FileDescriptor::DataArgs::buffer(string const &data)
{
	if (privBuffer)
		*privBuffer += data;
}
