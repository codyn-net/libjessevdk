#include "addressinfo.ih"

bool AddressInfo::next()
{
	if (!d_data->current || !d_data->current->ai_next)
		return false;
	
	d_data->current = d_data->current->ai_next;
	return true;
}
