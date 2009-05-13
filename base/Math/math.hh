#ifndef __BASE_MATH_H__
#define __BASE_MATH_H__

#include <base/Math/random.hh>

namespace base
{
	class Math
	{
		public:
			template <typename T>
			static T max(T const &a, T const &b);
			
			template <typename T>
			static T min(T const &a, T const &b);
	};
	
	template <typename T>
	T Math::max(T const &a, T const &b)
	{
		return a > b ? a : b;
	}
	
	template <typename T>
	T Math::min(T const &a, T const &b)
	{
		return a < b ? a : b;
	}
}

#endif /* __BASE_MATH_H__ */

