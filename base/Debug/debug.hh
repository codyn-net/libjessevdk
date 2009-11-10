#ifndef __BASE_DEBUG_H__
#define __BASE_DEBUG_H__

#include <iostream>
#include <string>

#define debug_out(domain) (base::Debug::out(base::Debug::Domain::domain, #domain,  __FILE__, __FUNCTION__, __LINE__))

#define debug_base (debug_out(Base))
#define debug_network (debug_out(Network))
#define debug_data (debug_out(Data))
#define debug_os (debug_out(OS))
#define debug_modules (debug_out(Modules))

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
					Base = 1 << 0,
					Network = 1 << 1,
					Data = 1 << 2,
					OS = 1 << 3,
					Modules = 1 << 4,
					User = 1 << 10
				};
			};
			
			static void enable(std::ostream &stream, int domain);

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
