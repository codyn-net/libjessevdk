#include "filedescriptor.ih"

void FileDescriptor::writeLine(string const &line)
{
	write(line + "\n");
}
