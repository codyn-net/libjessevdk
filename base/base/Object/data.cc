#include "object.ih"

Object::Data::Data()
:
	disposing(false),
	refCount(1)
{
}
