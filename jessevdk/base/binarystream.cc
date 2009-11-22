#include "binarystream.hh"

using namespace jessevdk::base;
using namespace std;

BinaryStream::BinaryStream(string const &filename)
{
	d_data = new Data();
	AddPrivateData(d_data);

	d_data->stream = new ifstream(filename.c_str(), ios::in | ios::binary);
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
