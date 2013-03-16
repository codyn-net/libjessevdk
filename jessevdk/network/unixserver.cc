#include "unixserver.hh"
#include <jessevdk/network/socketaddress.hh>
#include <sys/un.h>
#include <unistd.h>

using namespace std;
using namespace jessevdk::network;

string
UnixServer::Connection()
{
	return string("unix://:") + d_data->filename;
}

Client
UnixServer::Data::Accept()
{
	struct sockaddr_un addr;
	socklen_t len = sizeof(addr);
	struct sockaddr *ad = reinterpret_cast<struct sockaddr *>(&addr);

	int fd = ::accept(*listenSocket, ad, &len);
	return Client(fd, ad, len);
}

UnixServer::Data::~Data()
{
	::unlink(filename.c_str());
}

bool
UnixServer::Listen()
{
	::unlink(d_data->filename.c_str());
	return Server::Listen();
}

AddressInfo
UnixServer::ListenAddressInfo()
{
	return AddressInfo::Unix(d_data->filename);
}

bool
UnixServer::ListenOnSocket(Socket &socket)
{
	return socket.Listen(20);
}

void
UnixServer::Set(string const &filename)
{
	d_data->filename = filename;
}

void
UnixServer::SetData(Data *data)
{
	Server::SetData(data);
	d_data = data;
}

UnixServer::UnixServer(string const &filename)
{
	d_data = new Data();
	AddPrivateData(d_data);

	Set(filename);

	SetData(d_data);
}

UnixServer::UnixServer(Data *data)
{
	d_data = data;
	SetData(d_data);
}
