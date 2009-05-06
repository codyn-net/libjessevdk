#include "filedescriptor.ih"

void FileDescriptor::Data::close()
{
	int pfd = fd;

	if (sourceConnection)
		sourceConnection.disconnect();
	
	fd = -1;

	::close(pfd);
	onClosed(pfd);
}
