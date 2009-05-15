#include "sqlite.ih"

void SQLite::setSynchronous(bool synchronous) 
{
	if (synchronous)
	{
		query("PRAGMA synchronous = 1");
	}
	else
	{
		query("PRAGMA synchronous = 0");
	}
}
