#ifndef __NETWORK_CLIENT_H__
#define __NETWORK_CLIENT_H__

#include "Connection/connection.hh"
#include "AddressInfo/addressinfo.hh"

namespace network
{
	class Client : public Connection
	{
		public:
			/* Constructor/destructor */
			bool connect();
		protected:
			AddressInfo connectAddressInfo() = 0;
		private:
			/* Private functions */
		
	};
}

#endif /* __NETWORK_CLIENT_H__ */
