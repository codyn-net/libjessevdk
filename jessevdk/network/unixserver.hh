#ifndef __JESSEVDK_NETWORK_UNIX_SERVER_H__
#define __JESSEVDK_NETWORK_UNIX_SERVER_H__

#include <jessevdk/network/server.hh>

namespace jessevdk
{
namespace network
{
	class UnixServer : public Server
	{
		public:
			struct Data : public Server::Data
			{
				std::string filename;

				~Data();

				protected:
					virtual Client Accept();
			};

			/* Constructor/destructor */
			UnixServer(std::string const &filename = "");
			UnixServer(Data *data);

			/* Public functions */
			virtual bool Listen();
			virtual std::string Connection();
			virtual void SetData(Data *data);

			void Set(std::string const &filename);
		protected:
			virtual AddressInfo ListenAddressInfo();
			virtual bool ListenOnSocket(Socket &socket);
		private:
			/* Private functions */
			Data *d_data;
	};
}
}

#endif /* __JESSEVDK_NETWORK_UNIX_SERVER_H__ */
