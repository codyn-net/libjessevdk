#include "binarystream.ih"

void BinaryStream::reset() 
{
	if (!*this)
		d_data->stream->clear();
}
