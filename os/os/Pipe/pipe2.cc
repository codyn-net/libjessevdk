#include "pipe.ih"

Pipe::Pipe(int readEnd, int writeEnd) 
{
	d_data = new Data();
	addPrivateData(d_data);

	d_data->readEnd.assign(readEnd);
	d_data->writeEnd.assign(writeEnd);
	
	if (readEnd != -1)
		d_data->readEnd.attach();
}
