#ifndef __NETWORK_UNIX_SERVER_H__
#define __NETWORK_UNIX_SERVER_H__

#include "Server/server.hh"

namespace network
{
	class UnixServer : public Server
	{	
		struct Data : public Server::Data
		{
			std::string filename;
			
			~Data();

			protected:
				virtual Client accept();
		};
		
		Data *d_data;
		
		public:
			/* Constructor/destructor */
			UnixServer(std::string const &filename);

			/* Public functions */
			virtual bool listen();
		protected:
			virtual AddressInfo listenAddressInfo();
			virtual bool listenOnSocket(Socket &socket);
		private:
			/* Private functions */
		
	};
}

#endif /* __NETWORK_UNIX_SERVER_H__ */
