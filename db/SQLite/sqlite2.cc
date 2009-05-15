#include "sqlite.ih"

SQLite::SQLite() 
{
	d_data = new Data();
	addPrivateData(d_data);

	d_data->db = 0;
}
