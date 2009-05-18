#ifndef __DB_ROW_H__
#define __DB_ROW_H__

#include <base/Object/object.hh>
#include <sqlite3.h>
#include <map>

namespace db
{
	class Row : public base::Object
	{
		struct Data : public base::Object::PrivateData
		{
			/* Instance data */
			sqlite3 *db;
			sqlite3_stmt *statement;
			std::string error;
			
			std::map<std::string, size_t> columnMap;
			int lastStatement;
			
			~Data();
		};

		Data *d_data;

		public:
			/* Constructor/destructor */
			Row(sqlite3 *db, sqlite3_stmt *statement);
		
			/* Public functions */
			Row &next();
			
			operator bool() const;
			
			template <typename T>
			T get(std::string const &key) const;
			
			template <typename T>
			T get(size_t column) const;
			
			std::string const &error() const;
			size_t length() const;
		private:
			/* Private functions */
			void finish();
			void makeColumnMap();
	};
	
	inline Row::operator bool() const
	{
		return d_data->statement != 0 || d_data->lastStatement == SQLITE_DONE;
	}
	
	inline std::string const &Row::error() const
	{
		return d_data->error;
	}
	
	template <typename T>
	inline T Row::get(std::string const &key) const
	{
		return get<T>(d_data->columnMap[key]);
	}
	
	template <>
	inline std::string Row::get<std::string>(size_t column) const
	{
		return std::string(reinterpret_cast<char const *>(sqlite3_column_text(d_data->statement, column)));
	}
	
	template <>
	inline int Row::get<int>(size_t column) const
	{
		return sqlite3_column_int(d_data->statement, column);
	}
	
	template <>
	inline size_t Row::get<size_t>(size_t column) const
	{
		return static_cast<size_t>(sqlite3_column_int(d_data->statement, column));
	}
	
	template <>
	inline double Row::get<double>(size_t column) const
	{
		return sqlite3_column_double(d_data->statement, column);
	}
}

#endif /* __DB_ROW_H__ */
