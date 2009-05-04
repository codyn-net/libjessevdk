#ifndef __OS_PIPE_H__
#define __OS_PIPE_H__

#include "FileDescriptor/filedescriptor.hh"
#include "Object/object.hh"

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
			
			FileDescriptor &readEnd();
			FileDescriptor &writeEnd();
	};
	
	inline FileDescriptor &Pipe::readEnd()
	{
		return d_data->readEnd;
	}
	
	inline FileDescriptor &Pipe::writeEnd()
	{
		return d_data->writeEnd;
	}
}

#endif /* __OS_PIPE_H__ */

