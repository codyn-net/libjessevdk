#ifndef __BASE_RANDOM_H__
#define __BASE_RANDOM_H__

#include <limits.h>

namespace base
{
	template <typename T = double>
	class Random
	{
		public:
			static void seed(long int s);
			static T range(T min, T max); 
	};
	
	template <typename T>
	inline void Random<T>::seed(long int s)
	{
		srand48(s);
	}
	
	template <typename T>
	inline T Random<T>::range(T min, T max)
	{
		return drand48() * (max - min) + min;
	}
	
	template <>
	inline unsigned long Random<unsigned long>::range(unsigned long min, unsigned long max)
	{
		return static_cast<unsigned long>(static_cast<double>(lrand48()) / ULONG_MAX) * (max - min) + min;
	}

	template <>
	inline long Random<long>::range(long min, long max)
	{
		return static_cast<long>(static_cast<double>(lrand48()) / ULONG_MAX) * (max - min) + min;
	}
}

#endif /* __BASE_RANDOM_H__ */

