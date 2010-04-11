#ifndef __JESSEVDK_OS_FILE_DESCRIPTOR_H__
#define __JESSEVDK_OS_FILE_DESCRIPTOR_H__

#include <jessevdk/base/object.hh>
#include <glibmm.h>
#include <string>

namespace jessevdk
{
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

				void Buffer(std::string const &data);

				DataArgs(int fd, std::string *buffer);
				DataArgs *Clone() const;

				virtual ~DataArgs() {};

				private:
					std::string *privBuffer;
			};

			FileDescriptor(int fd = -1);

			FileDescriptor *Clone() const;

			void Assign(int fd);

			void Attach();
			void Detach();

			int Fd() const;

			void Write(std::string const &data);
			void WriteLine(std::string const &data);

			operator bool() const;
			operator int() const;

			void Close();

			base::signals::Signal<Glib::IOCondition> &OnIO();
			base::signals::Signal<int> &OnClosed();
			base::signals::Signal<DataArgs> &OnData();

		protected:
			struct Data : virtual public base::Object::PrivateData
			{
				friend class FileDescriptor;

				int fd;
				bool closing;

				sigc::connection sourceConnection;

				base::signals::Signal<Glib::IOCondition> onIO;
				base::signals::Signal<int> onClosed;
				base::signals::Signal<DataArgs> onData;

				std::string buffer;

				void WriteAll(std::string const &data);

				Data();
				~Data();

				private:
					bool OnIOSource(Glib::IOCondition condition);
					int Recv(std::string &data);
				protected:
					virtual void Close(bool destructed = false);

					virtual ssize_t Read(char *buffer, ssize_t len);
					virtual ssize_t Write(char const *buffer, ssize_t len);

					virtual base::Cloneable<FileDescriptor::DataArgs> CreateArgs(int fd, std::string *buffer);
			};

			FileDescriptor(bool createData);
			virtual void SetData(Data *data);
		private:
			Data *d_data;
	};

	inline base::signals::Signal<Glib::IOCondition> &FileDescriptor::OnIO()
	{
		return d_data->onIO;
	}

	inline base::signals::Signal<int> &FileDescriptor::OnClosed()
	{
		return d_data->onClosed;
	}

	inline base::signals::Signal<FileDescriptor::DataArgs> &FileDescriptor::OnData()
	{
		return d_data->onData;
	}

	inline int FileDescriptor::Fd() const
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
}

#endif /* __JESSEVDK_OS_FILE_DESCRIPTOR_H__ */

