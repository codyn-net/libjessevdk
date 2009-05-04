#include "pipe.ih"

Pipe::Pipe()
{
	d_data = new Data();
	addPrivateData(d_data);

	int pipefd[2];
	
	if (pipe(pipefd) == 0)
	{
		d_data->readEnd.assign(pipefd[0]);
		d_data->writeEnd.assign(pipefd[1]);
		
		d_data->readEnd.attach();
	}
}
