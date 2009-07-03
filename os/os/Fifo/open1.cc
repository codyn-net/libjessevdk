#include "fifo.ih"

bool Fifo::open(int oflag) 
{
	if (!d_data->ok)
		return false;
	
	int fd = ::open(d_data->filename.c_str(), oflag);
	assign(fd);
	
	return fd != -1;
}
