#ifndef __JESSEVDK_DB_SQLITE_ROW_H__
#define __JESSEVDK_DB_SQLITE_ROW_H__

#include <jessevdk/base/object.hh>
#include <sqlite3.h>
#include <map>

namespace jessevdk
{
namespace db
{
namespace sqlite
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
			Row &Next();

			operator bool() const;
			bool Done() const;

			template <typename T>
			T Get(std::string const &key) const;

			template <typename T>
			T Get(size_t column) const;

			std::string const &Error() const;
			size_t Length() const;
		private:
			/* Private functions */
			void Finish();
			void MakeColumnMap();
	};

	inline Row::operator bool() const
	{
		return d_data->statement != 0 || d_data->lastStatement == SQLITE_DONE;
	}

	inline bool Row::Done() const
	{
		return d_data->statement == 0 || d_data->lastStatement == SQLITE_DONE;
	}

	inline std::string const &Row::Error() const
	{
		return d_data->error;
	}

	template <typename T>
	inline T Row::Get(std::string const &key) const
	{
		return Get<T>(d_data->columnMap[key]);
	}

	template <>
	inline std::string Row::Get<std::string>(size_t column) const
	{
		return std::string(reinterpret_cast<char const *>(sqlite3_column_text(d_data->statement, column)));
	}

	template <>
	inline int Row::Get<int>(size_t column) const
	{
		return sqlite3_column_int(d_data->statement, column);
	}

	template <>
	inline size_t Row::Get<size_t>(size_t column) const
	{
		return static_cast<size_t>(sqlite3_column_int(d_data->statement, column));
	}

	template <>
	inline double Row::Get<double>(size_t column) const
	{
		return sqlite3_column_double(d_data->statement, column);
	}
}
}
}

#endif /* __JESSEVDK_DB_SQLITE_ROW_H__ */
