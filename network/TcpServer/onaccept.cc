#include "tcpserver.ih"
#include <errno.h>
#include <string.h>

bool TcpServer::onAccept(Glib::IOCondition condition)
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	int fd = ::accept(d_data->listenSocket, reinterpret_cast<struct sockaddr *>(&addr), &len);

	cout << "Accepting connection: " << fd << endl;

	Socket s = Socket(fd);
	
	if (s)
	{
		TcpConnection connection(s, addr);
		
		d_data->connections.push_back(connection);
		connection.onClosed().add(*this, &TcpServer::onConnectionClosed);

		d_data->onNewConnection(connection);
		return true;
	}
	else
	{
		cerr << "Error accepting client: " << strerror(errno) << endl;
	}
	
	return true;
}
