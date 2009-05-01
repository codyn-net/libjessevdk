#include "properties.ih"

Properties::Properties(Object &object)
:
	Object::Augmentation(object, new Data())
{
}
