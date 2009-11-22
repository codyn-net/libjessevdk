#ifndef __JESSEVDK_OS_PIPE_H__
#define __JESSEVDK_OS_PIPE_H__

#include <jessevdk/os/filedescriptor.hh>
#include <jessevdk/base/object.hh>

namespace jessevdk
{
namespace os
{
	class Pipe : public base::Object
	{
		struct Data : base::Object::PrivateData
		{
			FileDescriptor readEnd;
			FileDescriptor writeEnd;
		};

		Data *d_data;

		public:
			Pipe();
			Pipe(int readEnd, int writeEnd);

			FileDescriptor &ReadEnd();
			FileDescriptor &WriteEnd();
	};

	inline FileDescriptor &Pipe::ReadEnd()
	{
		return d_data->readEnd;
	}

	inline FileDescriptor &Pipe::WriteEnd()
	{
		return d_data->writeEnd;
	}
}
}

#endif /* __JESSEVDK_OS_PIPE_H__ */

