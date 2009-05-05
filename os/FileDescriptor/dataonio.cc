#include "filedescriptor.ih"

bool FileDescriptor::Data::onIO(Glib::IOCondition condition)
{
	if (condition == Glib::IO_HUP)
	{
		close();
		return false;
	}
	
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

		cerr << "Error occurred: " << len << ", " << strerror(errno) << endl;
		close();
		return false;
	}
	
	this->buffer += buffer;

	Cloneable<DataArgs> args = createArgs(fd, &(this->buffer));
	this->buffer = "";

	onData(*args);
	return true;
}
