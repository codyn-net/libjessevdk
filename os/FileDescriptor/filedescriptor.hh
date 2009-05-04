#ifndef __OS_FILE_DESCRIPTOR_H__
#define __OS_FILE_DESCRIPTOR_H__

#include "Object/object.hh"
#include <glibmm.h>
#include <string>

namespace os
{
	class FileDescriptor : public base::Object
	{
		public:
			struct DataArgs
			{
				friend class FileDescriptor;
				
				int fd;
				std::string data;
				
				void buffer(std::string const &data);
				
				private:
					DataArgs(int fd, std::string *buffer);
					std::string *privBuffer;
			};

			FileDescriptor(int fd = -1);
			
			void assign(int fd);
			
			void attach();
			int fd() const;

			void write(std::string const &data);
			void writeLine(std::string const &data);
			
			void close();
			
			base::signals::Signal<int> &onClosed();
			base::signals::Signal<DataArgs &> &onData();

		protected:
			struct Data : public base::Object::PrivateData
			{
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

				Glib::RefPtr<Glib::IOSource> source;

				base::signals::Signal<int> onClosed;
				base::signals::Signal<DataArgs &> onData;
			
				std::string buffer;
			
				bool onIO(Glib::IOCondition condition);
				virtual void close();
			};

			FileDescriptor(Data *data);
			void construct(int fd, Data *data);
		private:
			Data *d_data;

			void determineType();
	};
	
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
}

#endif /* __OS_FILE_DESCRIPTOR_H__ */

