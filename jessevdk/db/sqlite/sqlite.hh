#ifndef __JESSEVDK_DB_SQLITE_SQLITE_H__
#define __JESSEVDK_DB_SQLITE_SQLITE_H__

#include <jessevdk/base/object.hh>
#include <jessevdk/db/sqlite/row.hh>

#include <sqlite3.h>
#include <vector>
#include <sstream>

namespace jessevdk
{
namespace db
{
namespace sqlite
{
	class SQLite : public base::Object
	{
		struct Data : public base::Object::PrivateData
		{
			sqlite3 *db;
			std::string error;

			~Data();
		};

		Data *d_data;

		public:
			class Query : base::Object
			{
				friend class SQLite;

				struct Data : public base::Object::PrivateData
				{
					std::stringstream data;
					SQLite &db;

					Data(SQLite &db);
				};

				Data *d_data;

				public:
					struct End
					{
					};

					template <typename T>
					Query &operator<<(T const &val);

					Row operator<<(End const &ed);
				private:
					Query(SQLite &db);
			};

			/* Constructor/destructor */
			SQLite(std::string const &filename);
			SQLite();

			/* Public functions */
			operator bool() const;
			std::string const &Error() const;

			Row operator()(std::string const &query);
			Query operator()();

			void Begin();
			void Commit();
			void Rollback();

			size_t LastInsertId() const;

			void SetSynchronous(bool synchronous);

			static std::string Serialize(std::vector<std::string> const &vec);
			static std::string Serialize(std::vector<double> const &vec);

			static std::string Serialize(std::string const &s);
			static std::string Serialize(double d);
		private:
			/* Private functions */

	};

	inline std::string const &SQLite::Error() const
	{
		return d_data->error;
	}

	inline SQLite::operator bool() const
	{
		return d_data->db != 0;
	}

	inline SQLite::Query SQLite::operator()()
	{
		return Query(*this);
	}

	inline SQLite::Query::Data::Data(SQLite &db)
	:
		db(db)
	{
	}

	inline SQLite::Query::Query(SQLite &db)
	{
		d_data = new Data(db);
		AddPrivateData(d_data);
	}

	template <typename T>
	SQLite::Query &SQLite::Query::operator<<(T const &val)
	{
		d_data->data << val;
		return *this;
	}

	inline Row SQLite::Query::operator<<(SQLite::Query::End const &ed)
	{
		return d_data->db(d_data->data.str());
	}
}
}
}

#endif /* __JESSEVDK_DB_SQLITE_SQLITE_H__ */
