#include "fifo.ih"

void Fifo::close() 
{
	FileDescriptor::close();
	
	if (d_data->ok)
		unlink(d_data->filename.c_str());
}
