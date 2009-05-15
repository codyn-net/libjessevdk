#include "sqlite.ih"

SQLite::Data::~Data() 
{
	if (db)
		sqlite3_close(db);
}
