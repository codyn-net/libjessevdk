#ifndef _CONNECTION_HPP_INCLUDED_
#define _CONNECTION_HPP_INCLUDED_

#include <sys/types.h>
#ifdef _WIN32
#define WIN32_MEAN_AND_LEAN
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#endif
#include <exception>
#include <string>

class ConnectionClosedByRemote {};
class ConnectionOutOfMemory {};
class ConnectionDNSError {};
class ConnectionRefused {};
class ConnectionProtocolError {};
class ConnectionSocketError {
	std::string d_msg;
public:
	ConnectionSocketError(std::string msg)
		: d_msg(msg)
	{}
	std::string const &what() {
		return d_msg;
	}
};

enum MessageType {MSG_UNKNOWN, MSG_VERSION, MSG_ASKDOUBLES, MSG_DOUBLES};

#if !defined(_WIN32)
typedef int SOCKET;
#else
typedef int socklen_t;
#endif

class Connection
{
	static unsigned const d_signature;
	static unsigned const d_headerLength;
	SOCKET d_fd; // fd of connect socket

public:
	static char const *d_version;
	struct Message {
		unsigned length;
		MessageType type;
		unsigned signature;
		char *data;
	};

private:
	Message d_msg;

public:
	Connection(SOCKET fd);
	~Connection();

	/* memory should not be freed, it's automatically freed the next
	 * call to receiveDoubleArray()
	 * On exit, count is filled with number of doubles received
	 */
	double *receiveDoubleArray(unsigned *count);
	void sendDoubleArray(double *data, unsigned count);

	Connection::Message *receiveMessage();
	void sendMessage(Connection::Message &msg);

private:
	void init();
	void deleteMessage();
	void receiveBytes(char *data, unsigned length);
	void sendBytes(char const *data, unsigned length);
};

#endif /* _CONNECTION_HPP_INCLUDED_ */
