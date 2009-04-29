#ifndef _WIN32
#include <unistd.h>
#endif
#include <errno.h>
#include <sstream>

#include "connection.hpp"

using namespace std;

const char *Connection::d_version = "Robot Arm Network Protocol 2.0";
unsigned const Connection::d_signature = 0x20484a4d;
unsigned const Connection::d_headerLength = 
	sizeof(Connection::Message) - sizeof (void *);

Connection::Connection(SOCKET fd)
	: d_fd(fd)
{
	init();
}

void Connection::init()
{
	d_msg.data = 0;
	d_msg.length = 0;
	d_msg.type = MSG_UNKNOWN;

#if defined(__APPLE__) || defined(__APPLE_CC__)
	// apples way to stop getting SIGPIPE
	int one = 1;
	setsockopt(d_fd, SOL_SOCKET, SO_NOSIGPIPE, (void *)&one, sizeof(int));
#endif
}



Connection::~Connection()
{
	deleteMessage();
#ifdef _WIN32
	shutdown(d_fd, SD_SEND);
	closesocket(d_fd);
#else
	close(d_fd);
#endif
}

void Connection::deleteMessage()
{
	if (d_msg.data) {
		delete [] d_msg.data;
		d_msg.data = 0;
	}
}

Connection::Message *Connection::receiveMessage()
{
	deleteMessage();

	// first get header
	receiveBytes(reinterpret_cast<char *>(&d_msg), d_headerLength);
	if (d_msg.signature != d_signature)
		throw ConnectionProtocolError();

	d_msg.data = new char[d_msg.length];

	// then get data
	receiveBytes(d_msg.data, d_msg.length);

	return &d_msg;
}

void Connection::sendMessage(Connection::Message &msg)
{
	// first send header
	msg.signature = d_signature;
	sendBytes(reinterpret_cast<char const *>(&msg), d_headerLength);
	
	// then data
	sendBytes(msg.data, msg.length);
}

void Connection::receiveBytes(char *data, unsigned length)
{
	int read = 0;
	unsigned total = 0;
	
	while (total != length) {
		read = recv(d_fd, data + total, length - total, 0);
		if (read == 0)
			throw ConnectionClosedByRemote();
		if (read == -1) {
			int e;
#ifdef _WIN32
			e = WSAGetLastError();
#else
			e = errno;
#endif
			ostringstream os;
			os << "Failed to recv: " << e; 

			throw ConnectionSocketError(os.str());
		}
		total += read;
	}
}

void Connection::sendBytes(char const *data, unsigned length)
{
	int sent = 0;
	unsigned total = 0;
	int flags = 0;

#if defined(linux)
	// Linux's way to stop getting SIGPIPE
	flags = MSG_NOSIGNAL;
#endif
	
	while (total != length) {
		sent = send(d_fd, data + total, length - total, flags);
		if (sent == -1 && errno == EPIPE)
			throw ConnectionClosedByRemote();
		if (sent == -1)
			throw ConnectionSocketError("Failed to send");
		total += sent;
	}
}

void Connection::sendDoubleArray(double *data, unsigned count)
{
	Message msg;
	msg.length = count * sizeof(double);
	msg.type = MSG_DOUBLES;
	msg.data = reinterpret_cast<char *>(data);
	sendMessage(msg);
}

double *Connection::receiveDoubleArray(unsigned *count)
{
	// first ask for doubles
	Message askmsg;
	askmsg.length = 0;
	askmsg.type = MSG_ASKDOUBLES;
	sendMessage(askmsg);

	// then receive double array
	Message *msg;
	do {
		msg = receiveMessage();
	} while (msg->type != MSG_DOUBLES);
	
	if (count)
		*count = msg->length / sizeof(double);

	// we can return this pointer, because it is valid until the next
	// call to d_connetion.receiveMessage()
	return reinterpret_cast<double *>(msg->data);
}
