#include "properties.ih"

vector<string> Properties::properties() const
{
	vector<string> result;
	
	for (map<string, Cloneable<PropertyBase> >::const_iterator iter = data<Data>()->properties.begin(); iter != data<Data>()->properties.end(); ++iter)
		result.push_back(iter->first);
	
	return result;
}
