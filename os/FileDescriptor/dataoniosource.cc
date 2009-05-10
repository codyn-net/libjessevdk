#include "filedescriptor.ih"

bool FileDescriptor::Data::onIOSource(Glib::IOCondition condition)
{
	if (condition == Glib::IO_HUP)
	{
		close();
		return false;
	}
	
	if (onIO(condition))
		return false;
	
	/* try to read something */
	string buffer;
	ssize_t len = recv(buffer);
	
	if (len < 1)
	{
		if (len < 0)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				return true;
		}

		close();
		return false;
	}
	
	this->buffer += buffer;
	
	Cloneable<DataArgs> args = createArgs(fd, &(this->buffer));
	this->buffer = "";
	
	onData(*args);
	return true;
}
