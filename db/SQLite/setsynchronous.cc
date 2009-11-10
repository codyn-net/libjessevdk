#include "sqlite.ih"

void SQLite::setSynchronous(bool synchronous) 
{
	bool ret;

	if (synchronous)
	{
		ret = query("PRAGMA synchronous = 1");
	}
	else
	{
		ret = query("PRAGMA synchronous = 0");
	}

	if (!ret)
	{
		d_data->error = "Invalid database";

		sqlite3_close(d_data->db);	
		d_data->db = 0;
	}
}
