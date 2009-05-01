#include "object.ih"

intptr_t Object::privateDataOffset(Object::PrivateData **data) const
{
	return (intptr_t)data - (intptr_t)&d_data;
}
