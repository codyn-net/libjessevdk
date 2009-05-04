#ifndef __MONITORING_SERVER_H__
#define __MONITORING_SERVER_H__

#include "Object/object.hh"
#include "Optimizer/optimizer.hh"
#include "TcpServer/tcpserver.hh"

#include <string>

namespace monitoring
{
	class Server : base::Object
	{
		struct Data : public base::Object::PrivateData
		{
			network::TcpServer server;
			base::Cloneable<optimization::Optimizer> optimizer;
			
			Data(std::string const &host, std::string const &port);
		};
		
		Data *d_data;
		
		public:
			/* Constructor/destructor */
			Server(std::string const &host, std::string const &port);

			/* Public functions */
			void attach(optimization::Optimizer &optimizer);			
		private:
			/* Private functions */
		
	};
}

#endif /* __MONITORING_SERVER_H__ */
