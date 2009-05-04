#include "filedescriptor.ih"

void FileDescriptor::determineType()
{
	struct stat buf;
	
	if (fstat(d_data->fd, &buf) == 0)
	{
		if (S_ISSOCK(buf.st_mode))
		{
			d_data->type = Data::Type::Socket;
		}
		else
		{
			d_data->type = Data::Type::Normal;
		}
	}
	else
	{
		d_data->type = Data::Type::Normal;
	}
}
