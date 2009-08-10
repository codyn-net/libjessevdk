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

			std::vector<std::string> split(std::string const &delim, size_t mmax = 0) const;
		
			operator char const *() const;
		
			template <typename Container>
			static std::string join(Container const &container, std::string const &delim);
			
			bool endsWith(std::string const &other);
			bool startsWith(std::string const &other);
			
			String &replace(std::string const &search, std::string const &replace);
			
			String operator*(size_t num) const;
			
			String strip() const;
			String rstrip() const;
			String lstrip() const;
			
			operator double () const;
			template <typename T>
			T convert() const;
			
			static String hex(char const *s, size_t num);
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
	
	template <typename T>
	T String::convert() const
	{
		std::stringstream s;
		s << *this;
		
		T ret;
		s >> ret;
		
		return ret;
	}
}

#endif /* __BASE_STRING_H__ */
