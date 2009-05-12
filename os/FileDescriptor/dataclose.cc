#include "filedescriptor.ih"

void FileDescriptor::Data::close()
{
	if (fd == -1 || closing)
		return;

	closing = true;

	if (sourceConnection)
		sourceConnection.disconnect();
	
	::close(fd);
	onClosed(fd);
	
	fd = -1;
}
