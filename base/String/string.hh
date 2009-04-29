#ifndef __BASE_STRING_H__
#define __BASE_STRING_H__

#include <vector>
#include <string>
#include <sstream>

namespace base
{
	class String : public std::string
	{
		public:
			String();
			String(char const *s);
			String(std::string const &s);

			std::vector<std::string> split(std::string const &delim) const;
		
			operator char const *() const;
		
			template <typename Container>
			static std::string join(Container const &container, std::string const &delim);
			
			bool endsWith(std::string const &other);
			bool startsWith(std::string const &other);
	};

	template <typename Container>
	std::string String::join(Container const &container, std::string const &delim)
	{
		std::stringstream result;

		for (typename Container::const_iterator iter = container.begin(); iter != container.end(); ++iter)
		{
			if (iter != container.begin())
				result << delim;

			result << *iter;
		}
	
		return result.str();
	}
	
	inline String::String()
	{
	}

	inline String::String(char const *s)
	:
		std::string(s)
	{
	}

	inline String::String(std::string const &s)
	:
		std::string(s)
	{
	}
	
	inline String::operator char const *() const
	{
		return c_str();
	}
}

#endif /* __BASE_STRING_H__ */
