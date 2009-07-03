#include "fifo.ih"

Fifo::Fifo(string const &filename)
:
	FileDescriptor()
{
	d_data = new Data();
	addPrivateData(d_data);
	
	create(filename);
}
