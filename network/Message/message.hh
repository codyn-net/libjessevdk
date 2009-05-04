#ifndef __NETWORK_MESSAGE_H__
#define __NETWORK_MESSAGE_H__

#include "Object/object.hh"
#include "Properties/properties.hh"
#include <string>

namespace network
{
	class Message : public base::Object
	{
		struct Data : public base::Object::PrivateData
		{
			std::string serialized;
		};
		
		Data *d_data;
		
		public:
			/* Constructor/destructor */
			Message(base::Properties const &properties);
		
			/* Public functions */
			operator std::string() const;
		private:
			/* Private functions */
		
	};
}

#endif /* __NETWORK_MESSAGE_H__ */
