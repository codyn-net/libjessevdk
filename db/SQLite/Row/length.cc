#include "row.ih"

size_t Row::length() const
{
	if (*this)
	{
		return sqlite3_column_count(d_data->statement);
	}
	else
	{
		return 0;
	}
}
