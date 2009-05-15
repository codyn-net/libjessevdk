#include "sqlite.ih"

string SQLite::serialize(vector<double> const &vec) 
{
	vector<double>::const_iterator iter;
	stringstream s;
	
	for (iter = vec.begin(); iter != vec.end(); ++iter)
	{
		if (iter != vec.begin())
			s << ", ";

		s << String(serialize(*iter)).replace(",", "\\,");
	}
	
	return s.str();
}
