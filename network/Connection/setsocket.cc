#include "connection.ih"

void Connection::setSocket(Socket &socket) 
{
	if (d_data->socket)
		return;
	
	d_data->socket = socket;
	
	if (socket)
	{
		socket.onClosed().add(*d_data, &Connection::Data::onSocketClosed);
		
		assign(socket.socket());
		attach();
	}
}
