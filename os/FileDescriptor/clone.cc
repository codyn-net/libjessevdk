#include "filedescriptor.ih"

FileDescriptor *FileDescriptor::clone() const
{
	return new FileDescriptor(*this);
}
