#include "row.ih"

void Row::makeColumnMap() 
{
	d_data->columnMap.clear();
	
	size_t num = length();
	
	for (size_t i = 0; i < num; ++i)
	{
		d_data->columnMap[sqlite3_column_name(d_data->statement, i)] = i;
	}
}
