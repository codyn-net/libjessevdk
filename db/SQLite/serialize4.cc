#include "sqlite.ih"

string SQLite::serialize(double d) 
{
	stringstream s;
	
	s << d;
	
	return serialize(s.str());
}
