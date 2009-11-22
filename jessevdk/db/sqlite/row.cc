#include "row.hh"

using namespace std;
using namespace jessevdk::db::sqlite;

Row::Data::~Data()
{
	if (statement)
	{
		sqlite3_finalize(statement);
	}
}

void
Row::Finish()
{
	if (d_data->statement)
	{
		sqlite3_finalize(d_data->statement);
		d_data->statement = 0;
	}
}

size_t
Row::Length() const
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

void
Row::MakeColumnMap()
{
	d_data->columnMap.clear();

	size_t num = Length();

	for (size_t i = 0; i < num; ++i)
	{
		d_data->columnMap[sqlite3_column_name(d_data->statement, i)] = i;
	}
}

Row
&Row::Next()
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
		Finish();
	}
	else if (ret != SQLITE_ROW)
	{
		d_data->error = sqlite3_errmsg(d_data->db);
		Finish();
	}

	MakeColumnMap();

	return *this;
}

Row::Row(sqlite3 *db, sqlite3_stmt *statement)
{
	d_data = new Data();
	AddPrivateData(d_data);

	d_data->db = db;
	d_data->statement = statement;
	d_data->lastStatement = 0;

	if (!d_data->statement)
	{
		d_data->error = sqlite3_errmsg(db);
	}
	else
	{
		Next();
	}
}
