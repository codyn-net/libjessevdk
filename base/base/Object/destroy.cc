#include "object.ih"
#include <iostream>

void Object::destroy()
{
	if (!d_data || !d_data->refCount)
		return;

	if (!--(d_data->refCount))
	{
		/* Notify destruction */
		d_data->onDestroy(*this);
		d_data->destroy(*this);

		delete d_data;
		d_data = 0;
	}
	else if (!d_data->disposing)
	{
		dispose();
		d_data = 0;
	}
}
