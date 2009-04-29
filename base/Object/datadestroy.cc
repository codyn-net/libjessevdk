#include "object.ih"

void Object::Data::destroy(Object &parent) 
{
	for (vector<size_t>::reverse_iterator iter = managedData.rbegin(); iter != managedData.rend(); ++iter)
	{
		PrivateData **data = parent.privateDataAddress(*iter);
		
		if (*data)
		{
			PrivateData *item = *data;
			*data = 0;
			
			delete item;
		}
	}
}
