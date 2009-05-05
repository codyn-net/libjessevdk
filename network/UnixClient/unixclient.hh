#ifndef __NETWORK_UNIX_CLIENT_H__
#define __NETWORK_UNIX_CLIENT_H__

#include "Client/client.hh"

namespace network
{
	class UnixClient : public Client
	{
		struct Data : public base::Object::PrivateData
		{
			std::string filename;
		};
		
		public:
			UnixClient(std::string const &filename);
		protected:
			AddressInfo connectAddressInfo();
	};
}

#endif /* __NETWORK_UNIX_CLIENT_H__ */
