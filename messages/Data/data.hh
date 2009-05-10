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
	
			T message;
			char *buffer = new char[num + 1];

			if (!s.ignore(1, ' '))
				break;

			if (!s.read(buffer, num))
				break;

			buffer[num] = '\0';
			message.ParseFromString(buffer);
			delete[] buffer;

			data = data.substr(s.tellg());
			messages.push_back(message);
		}

		args.buffer(data);
	}
}

#endif /* __MESSAGES_DATA_H__ */
