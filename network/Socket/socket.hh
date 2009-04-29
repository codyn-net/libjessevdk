#ifndef __OPTIMIZATION_NETWORK_SOCKET_H__
#define __OPTIMIZATION_NETWORK_SOCKET_H__

#include "Object/object.hh"
#include "AddressInfo/addressinfo.hh"

namespace optimization
{
namespace network
{
	class Socket : public base::Object
	{
		struct Data	: public base::Object::PrivateData
		{
			AddressInfo info;
			int socket;
			
			~Data();
			void close();
			
			base::signals::Signal<> onClosed;
		};
		
		Data *d_data;
		
		public:
			struct Options
			{
				enum Values
				{
					Reuse = SO_REUSEADDR
				};
			};
			
			Socket(int socket = -1);
			Socket(AddressInfo info);
			
			int socket() const;
			
			operator bool() const;
			operator int() const;
			
			bool bind();
			bool setOption(Options::Values option);
			bool listen(size_t queue);
			bool connect();
			
			void close();
			
			base::signals::Signal<> &onClosed();
	};
	
	inline int Socket::socket() const
	{
		return d_data->socket;
	}
	
	inline Socket::operator int() const
	{
		return d_data->socket;
	}
	
	inline Socket::operator bool() const
	{
		return d_data->socket != -1;
	}
	
	inline base::signals::Signal<> &Socket::onClosed()
	{
		return d_data->onClosed;
	}
}
}

#endif /* __OPTIMIZATION_NETWORK_SOCKET_H__ */

