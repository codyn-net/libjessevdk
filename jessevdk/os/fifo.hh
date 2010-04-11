#ifndef __JESSEVDK_OS_FIFO_H__
#define __JESSEVDK_OS_FIFO_H__

#include <jessevdk/os/filedescriptor.hh>
#include <string>
#include <sys/stat.h>
#include <fcntl.h>

namespace jessevdk
{
namespace os
{
	class Fifo : public FileDescriptor
	{
		private:
			struct Data : public base::Object::PrivateData
			{
				std::string filename;
				bool ok;
			};

			Data *d_data;

		public:
			enum Flags
			{
				ReadOnly = O_RDONLY,
				WriteOnly = O_WRONLY,
				ReadWrite = O_RDWR,
				Append = O_APPEND,
				Creat = O_CREAT,
				Truncate = O_TRUNC,
				NonBlocking = O_NONBLOCK
			};

			/* Constructor/destructor */
			Fifo();
			Fifo(std::string const &filename);

			bool Open(std::string const &filename, int oflag = ReadOnly | Creat);
			bool Open(int oflag = ReadOnly | Creat);

			virtual void Close();
			bool Create(std::string const &filename);
		private:
	};
}
}

#endif /* __JESSEVDK_OS_FIFO_H__ */
