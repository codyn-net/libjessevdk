#include "binarystream.ih"

BinaryStream::BinaryStream(string const &filename)
{
	d_data = new Data();
	addPrivateData(d_data);
	
	d_data->stream = new ifstream(filename.c_str(), ios::in | ios::binary);
}
