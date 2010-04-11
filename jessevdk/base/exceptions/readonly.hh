#ifndef __JESSEVDK_BASE_EXCEPTIONS_READ_ONLY_H__
#define __JESSEVDK_BASE_EXCEPTIONS_READ_ONLY_H__

#include <jessevdk/base/exceptions/exception.hh>

namespace jessevdk
{
namespace base
{
namespace exceptions
{
	class ReadOnly : public Exception
	{
		std::string d_message;

		public:
			ReadOnly(std::string const &what) : Exception(what) {};
			~ReadOnly() throw() {};
	};
}
}
}

#endif /* __JESSEVDK_BASE_EXCEPTIONS_READ_ONLY_H__ */

