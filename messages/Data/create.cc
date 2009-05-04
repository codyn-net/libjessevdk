#include "data.ih"

bool Data::create(::google::protobuf::Message &message, string &serialized)
{
	if (!message.SerializeToString(&serialized))
		return false;
	
	stringstream s;
	
	size_t len = serialized.length();
	s << len << " " << serialized;
	
	serialized = s.str();
	return true;
}
