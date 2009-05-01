#include "tcpconnection.ih"

TcpConnection::Data::Data(Socket &socket, struct sockaddr_in const &address)
:
	socket(socket),
	address(address)
{
	if (socket)
	{
		source = Glib::IOSource::create(socket, Glib::IO_IN | Glib::IO_PRI | Glib::IO_ERR | Glib::IO_HUP);
		source->attach();
		
		socket.onClosed().add(*this, &TcpConnection::Data::onSocketClosed);
		source->connect(sigc::mem_fun(*this, &TcpConnection::Data::onIO));
	}
}
