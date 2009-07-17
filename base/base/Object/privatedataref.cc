#include "object.ih"

void Object::PrivateData::ref()
{
	++d_data->refCount;
}
