#include "object.ih"

void Object::Data::destroy(Object &parent) 
{
	for (vector<PrivateData *>::reverse_iterator iter = managedData.rbegin(); iter != managedData.rend(); ++iter)
	{
		delete *iter;
	}
}
