#include "binarystream.ih"

BinaryStream::Data::~Data()
{
	if (stream)
		delete stream;
}
