#include "connection.ih"

Connection::Connection(bool createData) 
:
	d_data(0)
{
	if (!createData)
		return;
	
	d_data = new Data();
	addPrivateData(d_data);
}
