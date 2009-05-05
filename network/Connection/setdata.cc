#include "connection.ih"

void Connection::setData(Data *data) 
{
	FileDescriptor::setData(data);
	d_data = data;
}
