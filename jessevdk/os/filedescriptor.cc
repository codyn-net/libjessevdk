#include "filedescriptor.hh"
#include <string.h>
#include <jessevdk/base/string.hh>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>

using namespace std;
using namespace jessevdk::os;
using namespace jessevdk::base;

void
FileDescriptor::Assign(int fd)
{
	if (d_data->fd != -1)
	{
		Close();
	}

	d_data->fd = fd;
}

void
FileDescriptor::Attach()
{
	if (d_data->fd == -1)
	{
		return;
	}

	Detach();

	d_data->sourceConnection = Glib::signal_io().connect(sigc::mem_fun(*d_data, &FileDescriptor::Data::OnIOSource), d_data->fd, Glib::IO_IN | Glib::IO_PRI | Glib::IO_ERR | Glib::IO_HUP);
}

FileDescriptor *
FileDescriptor::Clone() const
{
	return new FileDescriptor(*this);
}

void
FileDescriptor::Close()
{
	d_data->Close();
}

FileDescriptor::DataArgs::DataArgs(int fd, string *buffer)
:
	fd(fd),
	privBuffer(buffer)
{
	data = *buffer;
}

void
FileDescriptor::DataArgs::Buffer(string const &data)
{
	if (privBuffer)
	{
		*privBuffer += data;
	}
}

FileDescriptor::DataArgs *
FileDescriptor::DataArgs::Clone() const
{
	return new DataArgs(*this);
}

void
FileDescriptor::Data::Close(bool destructed)
{
	if (fd == -1 || closing)
	{
		return;
	}

	closing = true;

	if (sourceConnection)
	{
		sourceConnection.disconnect();
	}

	::close(fd);

	if (!destructed)
	{
		Ref();
	}

	onClosed(fd);

	fd = -1;

	if (!destructed)
	{
		Unref();
	}
}

FileDescriptor::Data::Data()
:
	closing(false)
{
}

Cloneable<FileDescriptor::DataArgs>
FileDescriptor::Data::CreateArgs(int fd, string *buffer)
{
	return DataArgs(fd, buffer);
}

FileDescriptor::Data::~Data()
{
	Close(true);
}

bool
FileDescriptor::Data::OnIOSource(Glib::IOCondition condition)
{
	if (condition & (Glib::IO_IN | Glib::IO_PRI))
	{
		if (!onIO(condition))
		{
			/* try to read something */
			string buffer;
			ssize_t len = Recv(buffer);

			if (len < 1)
			{
				if (len < 0)
				{
					cerr << "*** " << strerror(errno) << endl;
					if (errno == EAGAIN || errno == EWOULDBLOCK)
						return true;
				}

				Close();
				return false;
			}

			this->buffer.append(buffer);

			Cloneable<DataArgs> args = CreateArgs(fd, &(this->buffer));
			this->buffer = "";

			onData(*args);
		}
	}

	if (condition & (Glib::IO_HUP | Glib::IO_ERR))
	{
		Close();
		return false;
	}

	return true;
}

ssize_t
FileDescriptor::Data::Read(char *buffer, ssize_t len)
{
	return ::read(fd, buffer, len);
}

int
FileDescriptor::Data::Recv(string &data)
{
	char buffer[1024 * 1024];
	ssize_t len;

	len = this->Read(buffer, sizeof(buffer) - 1);

	data.clear();

	if (len >= 0)
	{
		buffer[len] = '\0';
		data.append(buffer, len);
	}

	return len;
}

ssize_t
FileDescriptor::Data::Write(char const *buffer, ssize_t len)
{
	return ::write(fd, buffer, len);
}

void
FileDescriptor::Data::WriteAll(string const &data)
{
	char const *ptr = data.c_str();
	ssize_t len = data.size();
	ssize_t written = 0;
	ssize_t num;

	if (this->fd == -1 || !len)
	{
		return;
	}

	do
	{
		num = this->Write(ptr + written, len - written);
		written += num;
	} while (num > 0 && len - written > 0);
}

void
FileDescriptor::Detach()
{
	if (d_data->fd == -1)
	{
		return;
	}

	if (d_data->sourceConnection)
	{
		d_data->sourceConnection.disconnect();
	}
}

FileDescriptor::FileDescriptor(int fd)
{
	d_data = new Data();
	AddPrivateData(d_data);

	d_data->fd = -1;
	Assign(fd);
}

FileDescriptor::FileDescriptor(bool createData)
{
	d_data = 0;

	if (!createData)
	{
		return;
	}

	d_data = new Data();
	AddPrivateData(d_data);

	d_data->fd = -1;
}

void
FileDescriptor::SetData(Data *data)
{
	d_data = data;
	d_data->fd = -1;
}

void
FileDescriptor::Write(string const &data)
{
	d_data->WriteAll(data);
}

void
FileDescriptor::WriteLine(string const &line)
{
	Write(line + "\n");
}
