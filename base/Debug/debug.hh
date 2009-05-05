#ifndef __BASE_DEBUG_H__
#define __BASE_DEBUG_H__

#include <iostream>
#include <string>

#define debug_out(domain) (base::Debug::out(base::Debug::Domain::domain, #domain,  __FILE__, __FUNCTION__, __LINE__))

#define debug_network (debug_out(Network))
#define debug_worker (debug_out(Worker))
#define debug_module (debug_out(Module))

namespace base
{
	class Debug
	{
		struct StreamBuf : public std::streambuf
		{
		};
		
		static Debug *s_instance;
		
		std::ostream &d_stream;
		std::ostream d_nostream;

		public:
			struct Domain
			{
				enum Values
				{
					None = 0,
					Network = 1 << 0,
					Worker = 1 << 1,
					Module = 1 << 2
				};
			};
			
			static void enable(std::ostream &stream, int domain);
			static void enableEnvironment(std::ostream &stream);
			static void enableEnvironment();

			static void enable(int domain);
			static void disable(int domain = Domain::None);
			
			static bool enabled(int domain);
			
			static std::ostream &out(int domain, std::string const &domainName, std::string const &file, std::string const &function, int line);		
			static std::ostream &out(int domain);
		private:
			int d_domain;

			Debug(int domain = Domain::None);
			Debug(std::ostream &stream, int domain = Domain::None);

			std::ostream &stream(int domain);
			int &domain();
	};
	
	inline std::ostream &Debug::out(int domain)
	{
		if (!s_instance)
			disable();
		
		return s_instance->stream(domain);
	}
	
	inline std::ostream &Debug::stream(int domain)
	{
		return d_domain & domain ? d_stream : d_nostream;
	}
	
	inline std::ostream &Debug::out(int domain, std::string const &domainName, std::string const &file, std::string const &function, int line) 
	{
		return out(domain) << "[" << domainName << "] " << file << ":" << function << " (" << line << "): ";
	}
	
	inline int &Debug::domain()
	{
		return d_domain;
	}
}

#endif /* __BASE_DEBUG_H__ */
