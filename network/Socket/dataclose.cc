#include "socket.ih"
#include <iostream>
using namespace std;

void Socket::Data::close()
{
	if (socket != -1)
	{
		cout << "Closing socket" << endl;
		::close(socket);
		socket = -1;
		
		onClosed();
	}
}
