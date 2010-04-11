#ifndef __JESSEVDK_BASE_EXCEPTIONS_BAD_VALUE_H__
#define __JESSEVDK_BASE_EXCEPTIONS_BAD_VALUE_H__

#include <jessevdk/base/exceptions/exception.hh>

namespace jessevdk
{
namespace base
{
namespace exceptions
{
	class BadValue : public Exception
	{
		std::string d_message;

		public:
			BadValue(std::string const &what) : Exception(what) {};
			~BadValue() throw() {};
	};
}
}
}

#endif /* __JESSEVDK_BASE_EXCEPTIONS_BAD_VALUE_H__ */

