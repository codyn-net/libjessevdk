#include "sqlite.ih"

void SQLite::begin() 
{
	query("BEGIN TRANSACTION");
}
