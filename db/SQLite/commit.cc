#include "sqlite.ih"

void SQLite::commit() 
{
	query("COMMIT TRANSACTION");	
}
