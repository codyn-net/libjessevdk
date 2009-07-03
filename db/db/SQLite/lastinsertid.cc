#include "sqlite.ih"

size_t SQLite::lastInsertId() const
{
	return sqlite3_last_insert_rowid(d_data->db);
}
