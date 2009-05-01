#include "properties.ih"

bool Properties::hasProperty(string const &name) const
{
	return data<Data>()->properties.find(name) != data<Data>()->properties.end();
}
