#include "row.ih"

Row::Data::~Data() 
{
	if (statement)
		sqlite3_finalize(statement);
}
