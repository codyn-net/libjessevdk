#include "fifo.ih"

bool Fifo::open(string const &filename, int oflag) 
{
	if (!d_data->ok)
		create(filename);
	
	return open(oflag);
}
