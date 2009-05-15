#include "row.ih"

Row &Row::next() 
{
	if (!d_data->statement)
	{
		d_data->lastStatement = 0;
		return *this;
	}
	
	int ret = sqlite3_step(d_data->statement);
	
	if (d_data->lastStatement == 0)
		d_data->lastStatement = ret;

	if (ret == SQLITE_DONE)
	{
		finish();
	}
	else if (ret != SQLITE_ROW)
	{
		d_data->error = sqlite3_errmsg(d_data->db);
		finish();
	}
	
	makeColumnMap();
	
	return *this;
}
