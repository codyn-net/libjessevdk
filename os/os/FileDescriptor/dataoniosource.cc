#include "filedescriptor.ih"

bool FileDescriptor::Data::onIOSource(Glib::IOCondition condition)
{
	if (condition & (Glib::IO_IN | Glib::IO_PRI))
	{
		if (!onIO(condition))
		{
			/* try to read something */
			string buffer;
			ssize_t len = recv(buffer);

			if (len < 1)
			{
				if (len < 0)
				{
					cerr << "*** " << strerror(errno) << endl;
					if (errno == EAGAIN || errno == EWOULDBLOCK)
						return true;
				}

				close();
				return false;
			}

			this->buffer.append(buffer);
	
			Cloneable<DataArgs> args = createArgs(fd, &(this->buffer));
			this->buffer = "";
	
			onData(*args);
		}
	}

	if (condition & (Glib::IO_HUP | Glib::IO_ERR))
	{
		close();
		return false;
	}
	
	return true;
}
