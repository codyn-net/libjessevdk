#include "object.ih"
#include <iostream>

void Object::copy(Object const &other)
{
	if (d_data == other.d_data)
		return;

	/* This should be interesting, and dirty */
	/*if (other.d_data)
	{
		vector<size_t> const &d = other.d_data->managedData;

		for (vector<size_t>::const_iterator iter = d.begin(); iter != d.end(); ++iter)
		{
			/// make sure to set data members correctly
			PrivateData **ptr = privateDataAddress(*iter);
		
			*ptr = *other.privateDataAddress(*iter);
		}
	}*/
	
	//cout << "Other data " << hex << other.d_data << endl;
	d_data = other.d_data;

	/* Increase ref count */
	if (d_data)
		++(d_data->refCount);
}
