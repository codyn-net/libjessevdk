#include "sqlite.ih"

void SQLite::rollback() 
{
	query("ROLLBACK TRANSACTION");
}
