#include "filedescriptor.ih"

void FileDescriptor::Data::close()
{
	int pfd = fd;

	::close(pfd);
	fd = -1;

	if (source)
	{
		source->destroy();
		source.reset();
	}

	onClosed(pfd);
}
