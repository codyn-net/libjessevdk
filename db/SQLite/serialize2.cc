#include "sqlite.ih"

string SQLite::serialize(string const &s) 
{
	return String(s).replace("'", "''");
}
