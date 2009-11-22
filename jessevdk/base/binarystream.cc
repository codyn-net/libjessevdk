#include "binarystream.hh"

using namespace jessevdk::base;
using namespace std;

BinaryStream::BinaryStream(string const &filename, Flags<Direction> const &direction)
{
	d_data = new Data();
	AddPrivateData(d_data);

	if ((direction & Direction::In) && (direction && Direction::Out))
	{
		d_data->stream = new fstream(filename.c_str(), ios::out | ios::in | ios::binary);
	}
	else if (direction & Direction::Out)
	{
		d_data->stream = new fstream(filename.c_str(), ios::out | ios::binary);
	}
	else
	{
		d_data->stream = new fstream(filename.c_str(), ios::in | ios::binary);
	}
}

BinaryStream::Data::~Data()
{
	if (stream)
	{
		delete stream;
	}
}

void
BinaryStream::Reset()
{
	if (!*this)
	{
		d_data->stream->clear();
	}
}
