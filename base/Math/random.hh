#ifndef __BASE_MATH_RANDOM_H__
#define __BASE_MATH_RANDOM_H__

#include <limits.h>
#include <time.h>
#include <base/Object/object.hh>

namespace base
{
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
}
}

#endif /* __BASE_MATH_RANDOM_H__ */

