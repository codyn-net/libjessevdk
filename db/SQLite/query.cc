#include "sqlite.ih"

Row SQLite::query(string const &query) 
{
	if (!*this)
		return Row(0, 0);

	sqlite3_stmt *statement;
	int ret = sqlite3_prepare_v2(d_data->db, query.c_str(), -1, &statement, 0);
	
	if (ret != SQLITE_OK)
	{
		stringstream s;

		s << "Error in query: '" << query << "' => " << sqlite3_errmsg(d_data->db);
		d_data->error = s.str();
		
		if (statement)
		{
			sqlite3_finalize(statement);
			statement = 0;
		}
	}
	
	return Row(d_data->db, statement);
}
