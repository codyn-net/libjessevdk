#include "fifo.hh"
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;
using namespace jessevdk::os;

void
Fifo::Close()
{
	FileDescriptor::Close();

	if (d_data->ok)
	{
		unlink(d_data->filename.c_str());
	}
}

bool
Fifo::Create(string const &filename)
{
	int ret = mkfifo(filename.c_str(), 0600);

	d_data->filename = filename;
	d_data->ok = ret == 0;

	return d_data->ok;
}

Fifo::Fifo(string const &filename)
:
	FileDescriptor()
{
	d_data = new Data();
	AddPrivateData(d_data);

	Create(filename);
}

bool
Fifo::Open(int oflag)
{
	if (!d_data->ok)
	{
		return false;
	}

	int fd = ::open(d_data->filename.c_str(), oflag);
	Assign(fd);

	return fd != -1;
}

bool
Fifo::Open(string const &filename, int oflag)
{
	if (!d_data->ok)
	{
		Create(filename);
	}

	return Open(oflag);
}
