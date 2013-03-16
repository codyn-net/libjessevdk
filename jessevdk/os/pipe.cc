#include "pipe.hh"
#include <unistd.h>

using namespace std;
using namespace jessevdk::os;

Pipe::Pipe()
{
	d_data = new Data();
	AddPrivateData(d_data);

	int pipefd[2];

	if (pipe(pipefd) == 0)
	{
		d_data->readEnd.Assign(pipefd[0]);
		d_data->writeEnd.Assign(pipefd[1]);

		d_data->readEnd.Attach();
	}
}

Pipe::Pipe(int readEnd, int writeEnd)
{
	d_data = new Data();
	AddPrivateData(d_data);

	d_data->readEnd.Assign(readEnd);
	d_data->writeEnd.Assign(writeEnd);

	if (readEnd != -1)
	{
		d_data->readEnd.Attach();
	}
}
