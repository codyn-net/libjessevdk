#ifndef __BASE_EXCEPTIONS_H__
#define __BASE_EXCEPTIONS_H__

#include <exception>

namespace base
{
namespace exceptions
{
	class bad_value : public std::exception
	{
		std::string d_what;
		
		public:
			bad_value(std::string const &what);
			~bad_value() throw() {};
			char const *what() const throw();
	};
	
	inline bad_value::bad_value(std::string const &what)
	:
		d_what(what)
	{	
	}
	
	inline char const *bad_value::what() const throw()
	{
		return d_what.c_str();
	}
}
}

#endif /* __BASE_EXCEPTIONS_H__ */

