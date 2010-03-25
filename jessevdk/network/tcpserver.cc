#include "tcpserver.hh"
#include <sstream>

using namespace jessevdk::network;
using namespace std;
using namespace jessevdk::base;

string
TcpServer::Connection()
{
	return string("tcp://") + ListenSocket().Address().Host(true) + ":" + d_data->port;
}

Client
TcpServer::Data::Accept()
{
	struct sockaddr_storage addr;
	socklen_t len = sizeof(addr);

	struct sockaddr *ad = reinterpret_cast<struct sockaddr *>(&addr);

	int fd = ::accept(*listenSocket, ad, &len);

	return Client(fd, ad, len);
}

void
TcpServer::Initialize(string const &host, string const &port)
{
	d_data = new Data();
	AddPrivateData(d_data);

	Set(host, port);
	SetData(d_data);
}

AddressInfo
TcpServer::ListenAddressInfo()
{
	return AddressInfo::Tcp(d_data->host, d_data->port);
}

bool
TcpServer::ListenOnSocket(Socket &socket)
{
	return socket.Listen(20);
}

void
TcpServer::Set(string const &host, string const &port)
{
	d_data->host = host;
	d_data->port = port;
}

void
TcpServer::Set(string const &host, size_t port)
{
	stringstream s;
	s << port;

	Set(host, s.str());
}

void
TcpServer::Set(string const &port)
{
	Set("", port);
}

void
TcpServer::Set(size_t port)
{
	Set("", port);
}

TcpServer::TcpServer(Data *data)
{
	SetData(data);
}

TcpServer::TcpServer(size_t port)
{
	stringstream s;
	s << port;

	Initialize("", s.str());
}

TcpServer::TcpServer(string const &host, size_t port)
{
	stringstream s;
	s << port;

	Initialize(host, s.str());
}

TcpServer::TcpServer(string const &host, string const &port)
{
	Initialize(host, port);
}

TcpServer::TcpServer(string const &port)
{
	Initialize("", port);
}

void
TcpServer::SetData(Data *data)
{
	Server::SetData(data);
	d_data = data;
}
