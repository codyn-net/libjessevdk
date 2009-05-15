#include "row.ih"

void Row::finish() 
{
	if (d_data->statement)
	{
		sqlite3_finalize(d_data->statement);
		d_data->statement = 0;
	}
}
