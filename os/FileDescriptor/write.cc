#include "filedescriptor.ih"

void FileDescriptor::write(string const &data)
{
	char const *ptr = data.c_str();
	ssize_t len = data.size();
	ssize_t written = 0;
	ssize_t num;
	
	if (d_data->fd == -1 || !len)
		return;
	
	do
	{
		if (d_data->type == Data::Type::Socket)
		{
			num = ::send(d_data->fd, ptr + written, len - written, MSG_NOSIGNAL);
		}
		else
		{
			num = ::write(d_data->fd, ptr + written, len - written);
		}
		
		written += num;
	} while (num > 0 && len - written > 0);
}
