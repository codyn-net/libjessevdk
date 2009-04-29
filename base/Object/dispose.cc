#include "object.ih"

bool Object::dispose() 
{
	if (!d_data)
		return false;
	
	d_data->disposing = true;
	ref();

	for (vector<size_t>::reverse_iterator iter = d_data->managedData.rbegin(); d_data && iter != d_data->managedData.rend(); ++iter)
	{
		PrivateData *data = *privateDataAddress(*iter);
		
		if (!data)
			continue;
			
		if (!data->dispose(*this))
		{
			unref();

			if (d_data)
				d_data->disposing = false;

			return false;
		}
	}

	unref();

	if (d_data)
		d_data->disposing = false;
	
	return true;
}
