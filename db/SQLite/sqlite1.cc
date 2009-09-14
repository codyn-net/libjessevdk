#include "sqlite.ih"

SQLite::SQLite(string const &filename) 
{
	d_data = new Data();
	addPrivateData(d_data);
	
	if (sqlite3_open(filename.c_str(), &d_data->db) != SQLITE_OK)
	{
		d_data->error = sqlite3_errmsg(d_data->db);
		sqlite3_close(d_data->db);
		
		d_data->db = 0;
		
		cerr << "Error while opening database `" << filename << "`: " << d_data->error << endl;
	}
	else
	{
		setSynchronous(false);
	}
}
