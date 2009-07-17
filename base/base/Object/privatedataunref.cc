#include "object.ih"

void Object::PrivateData::unref()
{
	if (d_data->refCount > 0)
	{
		if (--d_data->refCount == 0)
		{
			Data *data = d_data;
			
			d_data->destroy();
			delete data;
		}
	}
}
