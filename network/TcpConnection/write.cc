#include "tcpconnection.ih"

void TcpConnection::write(string const &data)
{
	char const *ptr = data.c_str();
	ssize_t len = data.size();
	ssize_t written = 0;
	ssize_t num;
	
	if (!d_data->socket || !len)
		return;
	
	do
	{
		num = ::send(d_data->socket, ptr + written, len - written, MSG_NOSIGNAL);
		written += num;
	} while (num > 0 && len - written > 0);
}
