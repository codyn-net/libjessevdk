#include "object.ih"

bool Object::disposing() const
{
	return d_data ? d_data->disposing : false;
}
