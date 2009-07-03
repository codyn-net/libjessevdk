#include "filedescriptor.ih"

FileDescriptor::DataArgs *FileDescriptor::DataArgs::clone() const
{
	return new DataArgs(*this);
}
