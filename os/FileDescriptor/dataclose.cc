#include "filedescriptor.ih"

void FileDescriptor::Data::close()
{
	int pfd = fd;

	if (sourceConnection)
		sourceConnection.disconnect();
	
	::close(pfd);
	onClosed(pfd);

	fd = -1;
}
