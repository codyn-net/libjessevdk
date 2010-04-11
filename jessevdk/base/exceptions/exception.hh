#ifndef __JESSEVDK_BASE_EXCEPTIONS_EXCEPTION_H__
#define __JESSEVDK_BASE_EXCEPTIONS_EXCEPTION_H__

#include <exception>

namespace jessevdk
{
namespace base
{
namespace exceptions
{
	class Exception : public std::exception
	{
		std::string d_what;

		public:
			Exception(std::string const &what);

			~Exception() throw() {};
			char const *what() const throw();
	};

	inline Exception::Exception(std::string const &what)
	:
		d_what(what)
	{
	}

	inline char const *Exception::what() const throw()
	{
		return d_what.c_str();
	}
}
}
}

#endif /* __JESSEVDK_BASE_EXCEPTIONS_EXCEPTION_H__ */

