#include "row.ih"

Row::Row(sqlite3 *db, sqlite3_stmt *statement) 
{
	d_data = new Data();
	addPrivateData(d_data);
	
	d_data->db = db;
	d_data->statement = statement;
	d_data->lastStatement = 0;
	
	if (!d_data->statement)
	{
		d_data->error = sqlite3_errmsg(db);
	}
	else
	{
		next();
	}
}
