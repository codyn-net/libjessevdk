#include "tcpconnection.ih"

void TcpConnection::writeLine(string const &line)
{
	write(line + "\n");
}
