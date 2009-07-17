#include "object.ih"

void Object::addPrivateData(PrivateData *data) 
{
	d_data->managedData.push_back(data);
	
	data->setData(d_data);
}
