#include "tcpconnection.ih"
#include <string.h>

bool TcpConnection::Data::onIO(Glib::IOCondition condition)
{
	if (condition == Glib::IO_HUP)
	{
		socket.close();
		return false;
	}
	
	/* try to read something */
	char buffer[1024];
	ssize_t len = recv(socket, buffer, 1024 - 1, 0);
	
	if (len < 1)
	{
		if (len < 0)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				return true;
		}

		cerr << "Error occurred: " << len << ", " << strerror(errno) << endl;
		socket.close();
	}
	
	buffer[len] = '\0';
	onData(buffer);
	
	String all = this->buffer + buffer;
	vector<string> lines = all.split("\n");
	
	for (vector<string>::iterator iter = lines.begin(); iter < lines.end() - 1; ++iter)
	{
		onLine(*iter);
	}
	
	this->buffer = *(lines.end() - 1);
	return true;
}
