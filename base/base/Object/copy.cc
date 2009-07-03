#include "object.ih"
#include <iostream>

void Object::copy(Object const &other)
{
	if (d_data == other.d_data)
		return;

	d_data = other.d_data;

	/* Increase ref count */
	if (d_data)
		++(d_data->refCount);
}
