#include "filedescriptor.ih"

void FileDescriptor::Data::close()
{
	if (fd == -1)
		return;

	int pfd = fd;

	if (sourceConnection)
		sourceConnection.disconnect();
	
	::close(pfd);
	fd = -1;

	onClosed(pfd);
}
