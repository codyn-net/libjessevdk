#include "properties.hh"

using namespace std;
using namespace jessevdk::base::properties;

Properties::Properties(Object &object)
:
	Object::Augmentation(object, new Data())
{
}

vector<string>
Properties::Names() const
{
	vector<string> result;
	map<string, Cloneable<PropertyBase> > const &properties = Object::Augmentation::Data<Data>()->properties;
	map<string, Cloneable<PropertyBase> >::const_iterator iter;

	for (iter = properties.begin(); iter != properties.end(); ++iter)
	{
		result.push_back(iter->first);
	}

	return result;
}

bool
Properties::HasProperty(string const &name)
{
	map<string, Cloneable<PropertyBase> > const &properties = Object::Augmentation::Data<Data>()->properties;
	return properties.find(name) != properties.end();
}
