#ifndef __BASE_MATH_H__
#define __BASE_MATH_H__

#include <base/Math/random.hh>
#include <algorithm>
#include <cmath>

namespace base
{
	class Math
	{
		public:
			template <typename T>
			static T max(T const &a, T const &b);
			
			template <typename T>
			static T min(T const &a, T const &b);
			
			template <typename Container>
			static typename Container::value_type euclidean(Container const &container);
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
	
	template <typename Container>
	static typename Container::value_type euclidean(Container const &container)
	{
		typename Container::const_iterator iter;
		typename Container::value_type sum;
		
		for (iter = container.begin(); iter != container.end(); ++iter)
			sum += *iter * *iter;
		
		return ::sqrt(sum);
	}
}

#endif /* __BASE_MATH_H__ */

