#ifndef __MATH_RANDOM_H__
#define __MATH_RANDOM_H__

#include <limits.h>
#include <time.h>
#include <base/Object/object.hh>
#include <cmath>

namespace math
{
	template <typename T = double, size_t StateSize = 256>
	class RandomBase : public base::Object
	{
		struct Data : public base::Object::PrivateData
		{
			char state[StateSize];
			T max;
		};
		
		Data *d_data;

		public:
			RandomBase();
			RandomBase(unsigned int seed);

			void seed(unsigned int seed);
			
			T generate();
			operator T();

			T range(T min, T max);
			
			int intRange(T min, T max);
			
			template <typename Iterator>
			void shuffle(Iterator begin, Iterator end);
	};
	
	typedef RandomBase<> Random;
	
	template <typename T, size_t StateSize>
	inline RandomBase<T, StateSize>::RandomBase()
	{
		d_data = new Data();
		addPrivateData(d_data);

		d_data->max = static_cast<T>(RAND_MAX);
		this->seed(time(0));
	}
	
	template <typename T, size_t StateSize>
	inline RandomBase<T, StateSize>::RandomBase(unsigned int seed)
	{
		d_data = new Data();
		addPrivateData(d_data);

		d_data->max = static_cast<T>(RAND_MAX);
		this->seed(seed);
	}

	template <typename T, size_t StateSize>
	inline void RandomBase<T, StateSize>::seed(unsigned int seed)
	{
		char *oldstate = initstate(seed, d_data->state, StateSize);
		setstate(oldstate);
	}
	
	template <typename T, size_t StateSize>
	inline T RandomBase<T, StateSize>::generate()
	{
		char *prev = setstate(d_data->state);
		T ret = static_cast<T>(random()) / d_data->max;
		
		setstate(prev);
		return ret;
	}
	
	template <typename T, size_t StateSize>
	inline RandomBase<T, StateSize>::operator T()
	{
		return generate();
	}
	
	template <typename T, size_t StateSize>
	inline T RandomBase<T, StateSize>::range(T min, T max)
	{
		return generate() * (max - min) + min;
	}	
	
	template <typename T, size_t StateSize>
	inline int RandomBase<T, StateSize>::intRange(T min, T max)
	{
		return static_cast<int>(::round(generate() * (max - min) + min));
	}
	
	template <typename T, size_t StateSize>
	template <typename Iterator>
	void RandomBase<T, StateSize>::shuffle(Iterator begin, Iterator end)
	{
		Iterator iter;
		size_t num = end - begin;
		
		for (iter = begin; iter != end; ++iter)
		{
			int i = intRange(0, num - 1);
			typename Iterator::value_type value;
			
			/* Swap values */
			value = *iter;
			*iter = *(begin + i);
			*(begin + i) = value;
		}
	}
}

#endif /* __MATH_RANDOM_H__ */

