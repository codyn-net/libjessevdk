#ifndef __JESSEVDK_MATH_RANDOM_H__
#define __JESSEVDK_MATH_RANDOM_H__

#include <limits.h>
#include <time.h>
#include <jessevdk/base/object.hh>
#include <cmath>

namespace jessevdk
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
			enum
			{
				state_size = StateSize
			};

			RandomBase();
			RandomBase(unsigned int seed);

			void Seed(unsigned int seed);

			T Generate();
			operator T();

			T Range(T min, T max);

			int IntRange(T min, T max);

			char const *State() const;
			size_t Size() const;

			template <typename Iterator>
			void Shuffle(Iterator begin, Iterator end);
	};

	typedef RandomBase<> Random;

	template <typename T, size_t StateSize>
	inline RandomBase<T, StateSize>::RandomBase()
	{
		d_data = new Data();
		AddPrivateData(d_data);

		d_data->max = static_cast<T>(RAND_MAX);
		this->Seed(time(0));
	}

	template <typename T, size_t StateSize>
	inline RandomBase<T, StateSize>::RandomBase(unsigned int seed)
	{
		d_data = new Data();
		AddPrivateData(d_data);

		d_data->max = static_cast<T>(RAND_MAX);
		this->Seed(seed);
	}

	template <typename T, size_t StateSize>
	inline void RandomBase<T, StateSize>::Seed(unsigned int seed)
	{
		char *oldstate = InitState(seed, d_data->state, StateSize);
		::setstate(oldstate);
	}

	template <typename T, size_t StateSize>
	inline T RandomBase<T, StateSize>::Generate()
	{
		char *prev = SetState(d_data->state);
		T ret = static_cast<T>(Random()) / d_data->max;

		::setstate(prev);
		return ret;
	}

	template <typename T, size_t StateSize>
	inline RandomBase<T, StateSize>::operator T()
	{
		return Generate();
	}

	template <typename T, size_t StateSize>
	inline T RandomBase<T, StateSize>::Range(T min, T max)
	{
		return Generate() * (max - min) + min;
	}

	template <typename T, size_t StateSize>
	inline int RandomBase<T, StateSize>::IntRange(T min, T max)
	{
		return static_cast<int>(::round(Generate() * (max - min) + min));
	}

	template <typename T, size_t StateSize>
	inline char const *RandomBase<T, StateSize>::State() const
	{
		return d_data->state;
	}

	template <typename T, size_t StateSize>
	inline size_t RandomBase<T, StateSize>::Size() const
	{
		return StateSize;
	}

	template <typename T, size_t StateSize>
	template <typename Iterator>
	void RandomBase<T, StateSize>::Shuffle(Iterator begin, Iterator end)
	{
		Iterator iter;
		size_t num = end - begin;

		for (iter = begin; iter != end; ++iter)
		{
			int i = IntRange(0, num - 1);
			typename Iterator::value_type value;

			/* Swap values */
			value = *iter;
			*iter = *(begin + i);
			*(begin + i) = value;
		}
	}
}
}

#endif /* __JESSEVDK_MATH_RANDOM_H__ */

