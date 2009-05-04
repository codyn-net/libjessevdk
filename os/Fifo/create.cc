#include "fifo.ih"

bool Fifo::create(string const &filename) 
{
	int ret = mkfifo(filename.c_str(), 0600);
	
	d_data->filename = filename;
	d_data->ok = ret == 0;
	
	return d_data->ok;
}
