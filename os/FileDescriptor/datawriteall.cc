#include "filedescriptor.ih"

void FileDescriptor::Data::writeAll(string const &data)
{
	char const *ptr = data.c_str();
	ssize_t len = data.size();
	ssize_t written = 0;
	ssize_t num;
	
	if (this->fd == -1 || !len)
		return;

	do
	{
		num = this->write(ptr + written, len - written);
		written += num;
	} while (num > 0 && len - written > 0);	
}
