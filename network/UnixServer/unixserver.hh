#ifndef __NETWORK_UNIX_SERVER_H__
#define __NETWORK_UNIX_SERVER_H__

#include "Server/server.hh"

namespace network
{
	class UnixServer : public Server
	{	
		struct Data : public base::Object::PrivateData
		{
			std::string filename;
		};
		
		Data *d_data;
		
		public:
			/* Constructor/destructor */
			UnixServer(std::string const &filename);

			/* Public functions */
			virtual void close();
		protected:
			virtual int accept();
			virtual AddressInfo listenAddressInfo();
		private:
			/* Private functions */
		
	};
}

#endif /* __NETWORK_UNIX_SERVER_H__ */
