#ifndef __JESSEVDK_BASE_DEBUG_H__
#define __JESSEVDK_BASE_DEBUG_H__

#include <iostream>
#include <string>

#define debug_out(domain) (base::Debug::Out(base::Debug::Domain::domain, #domain,  __FILE__, __FUNCTION__, __LINE__))

#define debug_base (debug_out(Base))
#define debug_network (debug_out(Network))
#define debug_data (debug_out(Data))
#define debug_os (debug_out(OS))

namespace jessevdk
{
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
					Last = 1 << 3
				};
			};

			static void Enable(std::ostream &stream, int domain);

			static void Enable(int domain);
			static void Disable(int domain = Domain::None);

			static bool Enabled(int domain);

			static std::ostream &Out(int domain, std::string const &domainName, std::string const &file, std::string const &function, int line);
			static std::ostream &Out(int domain);
		private:
			int d_domain;

			Debug(int domain = Domain::None);
			Debug(std::ostream &stream, int domain = Domain::None);

			std::ostream &Stream(int domain);
			int &Domain();
	};

	inline std::ostream &Debug::Out(int domain)
	{
		if (!s_instance)
		{
			Disable();
		}

		return s_instance->Stream(domain);
	}

	inline std::ostream &Debug::Stream(int domain)
	{
		return d_domain & domain ? d_stream : d_nostream;
	}

	inline std::ostream &Debug::Out(int domain, std::string const &domainName, std::string const &file, std::string const &function, int line)
	{
		return Out(domain) << "[" << domainName << "] " << file << ":" << function << " (" << line << "): ";
	}

	inline int &Debug::Domain()
	{
		return d_domain;
	}
}
}

#endif /* __JESSEVDK_BASE_DEBUG_H__ */
