#include "filedescriptor.ih"

void FileDescriptor::Data::close(bool destructed)
{
	if (fd == -1 || closing)
		return;

	closing = true;

	if (sourceConnection)
	{
		sourceConnection.disconnect();
	}
	
	::close(fd);
	
	if (!destructed)
	{
		ref();
	}
	
	onClosed(fd);
	
	fd = -1;
	
	if (!destructed)
	{
		unref();
	}
}
