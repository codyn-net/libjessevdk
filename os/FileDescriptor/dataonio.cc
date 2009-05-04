#include "filedescriptor.ih"

bool FileDescriptor::Data::onIO(Glib::IOCondition condition)
{
	if (condition == Glib::IO_HUP)
	{
		close();
		return false;
	}
	
	/* try to read something */
	char buffer[1024];
	ssize_t len;
	
	if (type == Type::Socket)
	{
		len = recv(fd, buffer, 1024 - 1, 0);
	}
	else
	{
		len = read(fd, buffer, 1024 - 1);
	}
	
	if (len < 1)
	{
		if (len < 0)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				return true;
		}

		cerr << "Error occurred: " << len << ", " << strerror(errno) << endl;
		close();
	}
	
	buffer[len] = '\0';
	this->buffer += buffer;

	DataArgs args(fd, &(this->buffer));
	this->buffer = "";

	onData(args);
	return true;
}
