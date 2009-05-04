#include "tcpserver.ih"

bool TcpServer::onConnectionClosed(TcpConnection connection)
{
	for (vector<TcpConnection>::iterator iter = d_data->connections.begin(); iter != d_data->connections.end(); ++iter)
	{
		if (*iter == connection)
		{
			d_data->connections.erase(iter);
			break;
		}
	}
	
	return false;
}
