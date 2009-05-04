#ifndef __MESSAGES_DATA_H__
#define __MESSAGES_DATA_H__

#include "FileDescriptor/filedescriptor.hh"
#include <vector>
#include <string>
#include <sstream>
#include <google/protobuf/message.h>

namespace messages
{
	class Data
	{
		public:
			template <typename T>
			static void extract(os::FileDescriptor::DataArgs &args, std::vector<T> &messages);
			
			static bool create(::google::protobuf::Message &message, std::string &serialized);
	};
	
	template <typename T>
	void Data::extract(os::FileDescriptor::DataArgs &args, std::vector<T> &messages)
	{
		std::string data = args.data;
	
		while (true)
		{
			size_t num;
			std::stringstream s(data);

			if (!(s >> num))
			{
				break;
			}
	
			if (s.str().length() < num)
			{
				break;
			}
		
			T message;
		
			message.ParseFromString(s.str().substr(0, num));
			data = s.str().substr(num);
		
			messages.push_back(message);
		}

		args.buffer(data);
	}
}

#endif /* __MESSAGES_DATA_H__ */
