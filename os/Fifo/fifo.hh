#ifndef __OS_FIFO_H__
#define __OS_FIFO_H__

#include "FileDescriptor/filedescriptor.hh"
#include <string>
#include <sys/stat.h>
#include <fcntl.h>

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
				Create = O_CREAT,
				Truncate = O_TRUNC,
				NonBlocking = O_NONBLOCK
			};

			/* Constructor/destructor */
			Fifo();
			Fifo(std::string const &filename);
			
			bool open(std::string const &filename, int oflag = ReadOnly | Create);
			bool open(int oflag = ReadOnly | Create);
			
			virtual void close();
			bool create(std::string const &filename);
		private:
	};
}

#endif /* __OS_FIFO_H__ */
