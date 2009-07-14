#include "string.ih"

String String::strip() const
{
	return lstrip().rstrip();
}
