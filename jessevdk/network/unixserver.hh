#ifndef __JESSEVDK_NETWORK_UNIX_SERVER_H__
#define __JESSEVDK_NETWORK_UNIX_SERVER_H__

#include <jessevdk/network/server.hh>

namespace jessevdk
{
namespace network
{
	class UnixServer : public Server
	{
		struct Data : public Server::Data
		{
			std::string filename;

			~Data();

			protected:
				virtual Client Accept();
		};

		Data *d_data;

		public:
			/* Constructor/destructor */
			UnixServer(std::string const &filename = "");

			/* Public functions */
			virtual bool Listen();
			virtual std::string Connection();

			void Set(std::string const &filename);
		protected:
			virtual AddressInfo ListenAddressInfo();
			virtual bool ListenOnSocket(Socket &socket);
		private:
			/* Private functions */

	};
}
}

#endif /* __JESSEVDK_NETWORK_UNIX_SERVER_H__ */
