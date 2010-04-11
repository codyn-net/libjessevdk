#ifndef __JESSEVDK_BASE_STRING_H__
#define __JESSEVDK_BASE_STRING_H__

#include <vector>
#include <string>
#include <sstream>

namespace jessevdk
{
namespace base
{
	class String : public std::string
	{
		public:
			String();
			String(char const *s);
			String(std::string const &s);

			std::vector<std::string> Split(std::string const &delim, size_t mmax = 0) const;

			operator char const *() const;

			template <typename Container>
			static std::string Join(Container const &container, std::string const &delim);

			bool EndsWith(std::string const &other);
			bool StartsWith(std::string const &other);

			String &Replace(std::string const &search, std::string const &replace);

			String operator*(size_t num) const;

			String Strip() const;
			String StripRight() const;
			String StripLeft() const;

			operator double () const;
			template <typename T>
			T Convert() const;

			static String Hex(char const *s, size_t num);
	};

	template <typename Container>
	std::string String::Join(Container const &container, std::string const &delim)
	{
		std::stringstream result;

		for (typename Container::const_iterator iter = container.begin(); iter != container.end(); ++iter)
		{
			if (iter != container.begin())
			{
				result << delim;
			}

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
	T String::Convert() const
	{
		std::stringstream s;
		s << *this;

		T ret;
		s >> ret;

		return ret;
	}
}
}

#endif /* __JESSEVDK_BASE_STRING_H__ */
