#ifndef __DB_SQLITE_H__
#define __DB_SQLITE_H__

#include <base/Object/object.hh>
#include <db/SQLite/Row/row.hh>

#include <sqlite3.h>
#include <vector>
#include <sstream>

namespace db
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
					
					static End end();
				private:
					Query(SQLite &db);
			};

			/* Constructor/destructor */
			SQLite(std::string const &filename);
			SQLite();
		
			/* Public functions */
			operator bool() const;
			std::string const &error() const;
			
			Row query(std::string const &query);
			Query query();
			
			void begin();
			void commit();
			void rollback();
			
			size_t lastInsertId() const;
			
			void setSynchronous(bool synchronous);
			
			static std::string serialize(std::vector<std::string> const &vec);
			static std::string serialize(std::vector<double> const &vec);
			
			static std::string serialize(std::string const &s);
			static std::string serialize(double d);
		private:
			/* Private functions */
		
	};
	
	inline std::string const &SQLite::error() const
	{
		return d_data->error;
	}
	
	inline SQLite::operator bool() const
	{
		return d_data->db != 0;
	}
	
	inline SQLite::Query SQLite::query()
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
		addPrivateData(d_data);
	}
	
	template <typename T>
	SQLite::Query &SQLite::Query::operator<<(T const &val)
	{
		d_data->data << val;
		return *this;
	}
	
	inline SQLite::Query::End SQLite::Query::end()
	{
		return End();
	}
	
	inline Row SQLite::Query::operator<<(SQLite::Query::End const &ed)
	{
		return d_data->db.query(d_data->data.str());
	}
}

#endif /* __DB_SQLITE_H__ */
