#include "connection.ih"
#include <string.h>
#include <errno.h>

bool Connection::Data::onIO(Glib::IOCondition condition) 
{
	if (condition == Glib::IO_HUP || socket.addressInfo().socketType() != SOCK_DGRAM)
	{
		return FileDescriptor::Data::onIO(condition);
	}
	
	/* try to read something */
	char buffer[1024];
	ssize_t len;
	
	socklen_t slen = sizeof(lastAddress);
	len = recvfrom(fd, buffer, 1024 - 1, 0, reinterpret_cast<struct sockaddr *>(&lastAddress), &slen);
	
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
