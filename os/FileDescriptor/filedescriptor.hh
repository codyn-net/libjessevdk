#ifndef __OS_FILE_DESCRIPTOR_H__
#define __OS_FILE_DESCRIPTOR_H__

#include "Object/object.hh"
#include <glibmm.h>
#include <string>

namespace os
{
	class FileDescriptor : virtual public base::Object
	{
		public:
			struct DataArgs
			{
				friend class FileDescriptor;

				int fd;
				std::string data;
			
				void buffer(std::string const &data);

				DataArgs(int fd, std::string *buffer);
				DataArgs *clone() const;
			
				virtual ~DataArgs() {};

				private:
					std::string *privBuffer;
			};

			FileDescriptor(int fd = -1);
			
			void assign(int fd);
			
			void attach();
			int fd() const;

			void write(std::string const &data);
			void writeLine(std::string const &data);
			
			operator bool() const;
			operator int() const;
			
			void close();
			
			base::signals::Signal<Glib::IOCondition> &onIO();
			base::signals::Signal<int> &onClosed();
			base::signals::Signal<DataArgs &> &onData();

		protected:
			struct Data : virtual public base::Object::PrivateData
			{
				friend class FileDescriptor;

				struct Type
				{
					enum Values
					{
						Normal,
						Socket
					};
				};
				
				int fd;
				Type::Values type;

				sigc::connection sourceConnection;

				base::signals::Signal<Glib::IOCondition> onIO;
				base::signals::Signal<int> onClosed;
				base::signals::Signal<DataArgs &> onData;
			
				std::string buffer;
			
				virtual void close();
				~Data();
				
				private:
					bool onIOSource(Glib::IOCondition condition);
				protected:
					virtual int recv(std::string &data);
					virtual base::Cloneable<FileDescriptor::DataArgs> createArgs(int fd, std::string *buffer);
			};

			FileDescriptor(bool createData);
			virtual void setData(Data *data);
		private:
			Data *d_data;

			void determineType();
	};
	
	inline base::signals::Signal<Glib::IOCondition> &FileDescriptor::onIO()
	{
		return d_data->onIO;
	}
	
	inline base::signals::Signal<int> &FileDescriptor::onClosed()
	{
		return d_data->onClosed;
	}
	
	inline base::signals::Signal<FileDescriptor::DataArgs &> &FileDescriptor::onData()
	{
		return d_data->onData;
	}
	
	inline int FileDescriptor::fd() const
	{
		return d_data->fd;
	}
	
	inline FileDescriptor::operator bool() const
	{
		return d_data->fd != -1;
	}
	
	inline FileDescriptor::operator int() const
	{
		return d_data->fd;
	}
}

#endif /* __OS_FILE_DESCRIPTOR_H__ */

