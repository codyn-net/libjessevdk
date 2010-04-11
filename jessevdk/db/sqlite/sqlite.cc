#include "sqlite.hh"
#include <jessevdk/base/string.hh>

#include <sstream>

using namespace std;
using namespace jessevdk::db::sqlite;
using namespace jessevdk::base;

void
SQLite::Begin()
{
	(*this)("BEGIN TRANSACTION");
}

void
SQLite::Commit()
{
	(*this)("COMMIT TRANSACTION");
}

SQLite::Data::~Data()
{
	if (db)
	{
		sqlite3_close(db);
	}
}

size_t
SQLite::LastInsertId() const
{
	return sqlite3_last_insert_rowid(d_data->db);
}

Row
SQLite::operator()(string const &query)
{
	if (!*this)
	{
		return Row(0, 0);
	}

	sqlite3_stmt *statement;
	int ret = sqlite3_prepare_v2(d_data->db, query.c_str(), -1, &statement, 0);

	if (ret != SQLITE_OK)
	{
		d_data->error = sqlite3_errmsg(d_data->db);
		cerr << "Error in query: '" << query << "'" << endl << "\t => " << d_data->error << endl;

		if (statement)
		{
			sqlite3_finalize(statement);
			statement = 0;
		}
	}

	return Row(d_data->db, statement);
}

void
SQLite::Rollback()
{
	(*this)("ROLLBACK TRANSACTION");
}

string
SQLite::Serialize(vector<string> const &vec)
{
	vector<string>::const_iterator iter;
	stringstream s;

	for (iter = vec.begin(); iter != vec.end(); ++iter)
	{
		if (iter != vec.begin())
		{
			s << ", ";
		}

		s << String(Serialize(*iter)).Replace(",", "\\,");
	}

	return s.str();
}

string
SQLite::Serialize(string const &s)
{
	return String(s).Replace("'", "''");
}

string SQLite::Serialize(vector<double> const &vec)
{
	vector<double>::const_iterator iter;
	stringstream s;

	for (iter = vec.begin(); iter != vec.end(); ++iter)
	{
		if (iter != vec.begin())
		{
			s << ", ";
		}

		s << String(Serialize(*iter)).Replace(",", "\\,");
	}

	return s.str();
}

string
SQLite::Serialize(double d)
{
	stringstream s;

	s << d;
	return Serialize(s.str());
}

void
SQLite::SetSynchronous(bool synchronous)
{
	if (synchronous)
	{
		(*this)("PRAGMA synchronous = 1");
	}
	else
	{
		(*this)("PRAGMA synchronous = 0");
	}
}

SQLite::SQLite(string const &filename)
{
	d_data = new Data();
	AddPrivateData(d_data);

	if (sqlite3_open(filename.c_str(), &d_data->db))
	{
		d_data->error = sqlite3_errmsg(d_data->db);
		sqlite3_close(d_data->db);

		d_data->db = 0;

		cerr << "Error while opening database `" << filename << "`: " << d_data->error << endl;
	}
	else
	{
		SetSynchronous(false);
	}
}

SQLite::SQLite()
{
	d_data = new Data();
	AddPrivateData(d_data);

	d_data->db = 0;
}
