#ifndef __BASE_FUNCTIONAL_MEMCB_H__
#define __BASE_FUNCTIONAL_MEMCB_H__

#include <cstddef>

namespace base
{
namespace functional
{
	struct _NoneArg
	{
	};

	template <typename TObject, typename TReturnType, typename TArgType, size_t NumArgs, typename TExtraArgs = _NoneArg>
	class MemCbImpl
	{
	};
	
	template <typename TObject, typename TReturnType>
	class MemCbImpl<TObject, TReturnType, int, 0, _NoneArg>
	{
		typedef TReturnType (TObject::*Function)();

		TObject &d_object;
		Function d_function;

		public:
			MemCbImpl(TObject &object, Function function);
			
			TReturnType operator()();
	};
	
	template <typename TObject, typename TReturnType>
	MemCbImpl<TObject, TReturnType, int, 0, _NoneArg>::MemCbImpl(TObject &object, Function function)
	:
		d_object(object),
		d_function(function)
	{
	}

	template <typename TObject, typename TReturnType>
	TReturnType MemCbImpl<TObject, TReturnType, int, 0, _NoneArg>::operator()()
	{
		return (d_object.*d_function)();
	}
	
	template <typename TObject, typename TReturnType, typename TArgType>
	class MemCbImpl<TObject, TReturnType, TArgType, 1, _NoneArg>
	{
		typedef TReturnType (TObject::*Function)(TArgType);

		TObject &d_object;
		Function d_function;

		public:
			MemCbImpl(TObject &object, Function function);

			TReturnType operator()(TArgType arg);
	};
	
	template <typename TObject, typename TReturnType, typename TArgType>
	MemCbImpl<TObject, TReturnType, TArgType, 1, _NoneArg>::MemCbImpl(TObject &object, Function function)
	:
		d_object(object),
		d_function(function)
	{
	}
	
	template <typename TObject, typename TReturnType, typename TArgType>
	TReturnType MemCbImpl<TObject, TReturnType, TArgType, 1, _NoneArg>::operator()(TArgType arg)
	{
		return (d_object.*d_function)(arg);
	}
	
	template <typename TObject, typename TReturnType, typename TArgType>
	class MemCbImpl<TObject, TReturnType, TArgType const &, 1, _NoneArg>
	{
		typedef TReturnType (TObject::*Function)(TArgType const &);

		TObject &d_object;
		Function d_function;

		public:
			MemCbImpl(TObject &object, Function function);

			TReturnType operator()(TArgType const &arg);
	};
	
	template <typename TObject, typename TReturnType, typename TArgType>
	MemCbImpl<TObject, TReturnType, TArgType const &, 1, _NoneArg>::MemCbImpl(TObject &object, Function function)
	:
		d_object(object),
		d_function(function)
	{
	}
	
	template <typename TObject, typename TReturnType, typename TArgType>
	TReturnType MemCbImpl<TObject, TReturnType, TArgType const &, 1, _NoneArg>::operator()(TArgType const &arg)
	{
		return (d_object.*d_function)(arg);
	}
	
	template <typename TObject, typename TReturnType, typename TArgType>
	class MemCbImpl<TObject, TReturnType, TArgType, 2, _NoneArg>
	{
		typedef TReturnType (TObject::*Function)(TArgType, TArgType);

		TObject &d_object;
		Function d_function;

		public:
			MemCbImpl(TObject &object, Function function);

			TReturnType operator()(TArgType arg1, TArgType arg2);
	};
	
	template <typename TObject, typename TReturnType, typename TArgType>
	MemCbImpl<TObject, TReturnType, TArgType, 2, _NoneArg>::MemCbImpl(TObject &object, Function function)
	:
		d_object(object),
		d_function(function)
	{
	}
	
	template <typename TObject, typename TReturnType, typename TArgType>
	TReturnType MemCbImpl<TObject, TReturnType, TArgType, 2, _NoneArg>::operator()(TArgType arg1, TArgType arg2)
	{
		return (d_object.*d_function)(arg1, arg2);
	}

	template <typename TObject, typename TReturnType, typename TArgType>
	class MemCbImpl<TObject, TReturnType, TArgType const &, 2, _NoneArg>
	{
		typedef TReturnType (TObject::*Function)(TArgType const &);

		TObject &d_object;
		Function d_function;

		public:
			MemCbImpl(TObject &object, Function function);

			TReturnType operator()(TArgType const &arg1, TArgType const &arg2);
	};
	
	template <typename TObject, typename TReturnType, typename TArgType>
	MemCbImpl<TObject, TReturnType, TArgType const &, 2, _NoneArg>::MemCbImpl(TObject &object, Function function)
	:
		d_object(object),
		d_function(function)
	{
	}
	
	template <typename TObject, typename TReturnType, typename TArgType>
	TReturnType MemCbImpl<TObject, TReturnType, TArgType const &, 2, _NoneArg>::operator()(TArgType const &arg1, TArgType const &arg2)
	{
		return (d_object.*d_function)(arg1, arg2);
	}
	
	
	/* With extra user argument */
	template <typename TObject, typename TReturnType, typename TExtraArgs>
	class MemCbImpl<TObject, TReturnType, int, 0, TExtraArgs>
	{
		typedef TReturnType (TObject::*Function)(TExtraArgs const &args);

		TObject &d_object;
		Function d_function;
		TExtraArgs const &d_args;

		public:
			MemCbImpl(TObject &object, Function function, TExtraArgs const &args);
			
			TReturnType operator()();
	};
	
	template <typename TObject, typename TReturnType, typename TExtraArgs>
	MemCbImpl<TObject, TReturnType, int, 0, TExtraArgs>::MemCbImpl(TObject &object, Function function, TExtraArgs const &args)
	:
		d_object(object),
		d_function(function),
		d_args(args)
	{
	}

	template <typename TObject, typename TReturnType, typename TExtraArgs>
	TReturnType MemCbImpl<TObject, TReturnType, int, 0, TExtraArgs>::operator()()
	{
		return (d_object.*d_function)(d_args);
	}
	
	template <typename TObject, typename TReturnType, typename TArgType, typename TExtraArgs>
	class MemCbImpl<TObject, TReturnType, TArgType, 1, TExtraArgs>
	{
		typedef TReturnType (TObject::*Function)(TArgType, TExtraArgs const &);

		TObject &d_object;
		Function d_function;
		TExtraArgs const &d_args;

		public:
			MemCbImpl(TObject &object, Function function, TExtraArgs const &args);

			TReturnType operator()(TArgType arg);
	};
	
	template <typename TObject, typename TReturnType, typename TArgType, typename TExtraArgs>
	MemCbImpl<TObject, TReturnType, TArgType, 1, TExtraArgs>::MemCbImpl(TObject &object, Function function, TExtraArgs const &args)
	:
		d_object(object),
		d_function(function),
		d_args(args)
	{
	}
	
	template <typename TObject, typename TReturnType, typename TArgType, typename TExtraArgs>
	TReturnType MemCbImpl<TObject, TReturnType, TArgType, 1, TExtraArgs>::operator()(TArgType arg)
	{
		return (d_object.*d_function)(arg, d_args);
	}
	
	template <typename TObject, typename TReturnType, typename TArgType, typename TExtraArgs>
	class MemCbImpl<TObject, TReturnType, TArgType const &, 1, TExtraArgs>
	{
		typedef TReturnType (TObject::*Function)(TArgType const &, TExtraArgs const &);

		TObject &d_object;
		Function d_function;
		TExtraArgs const &d_args;

		public:
			MemCbImpl(TObject &object, Function function, TExtraArgs const &args);

			TReturnType operator()(TArgType const &arg);
	};
	
	template <typename TObject, typename TReturnType, typename TArgType, typename TExtraArgs>
	MemCbImpl<TObject, TReturnType, TArgType const &, 1, TExtraArgs>::MemCbImpl(TObject &object, Function function, TExtraArgs const &args)
	:
		d_object(object),
		d_function(function),
		d_args(args)
	{
	}
	
	template <typename TObject, typename TReturnType, typename TArgType, typename TExtraArgs>
	TReturnType MemCbImpl<TObject, TReturnType, TArgType const &, 1, TExtraArgs>::operator()(TArgType const &arg)
	{
		return (d_object.*d_function)(arg, d_args);
	}
	
	template <typename TObject, typename TReturnType, typename TArgType, typename TExtraArgs>
	class MemCbImpl<TObject, TReturnType, TArgType, 2, TExtraArgs>
	{
		typedef TReturnType (TObject::*Function)(TArgType, TArgType, TExtraArgs const &);

		TObject &d_object;
		Function d_function;
		TExtraArgs const &d_args;

		public:
			MemCbImpl(TObject &object, Function function, TExtraArgs const &args);

			TReturnType operator()(TArgType arg1, TArgType arg2);
	};
	
	template <typename TObject, typename TReturnType, typename TArgType, typename TExtraArgs>
	MemCbImpl<TObject, TReturnType, TArgType, 2, TExtraArgs>::MemCbImpl(TObject &object, Function function, TExtraArgs const &args)
	:
		d_object(object),
		d_function(function),
		d_args(args)
	{
	}
	
	template <typename TObject, typename TReturnType, typename TArgType, typename TExtraArgs>
	TReturnType MemCbImpl<TObject, TReturnType, TArgType, 2, TExtraArgs>::operator()(TArgType arg1, TArgType arg2)
	{
		return (d_object.*d_function)(arg1, arg2, d_args);
	}

	template <typename TObject, typename TReturnType, typename TArgType, typename TExtraArgs>
	class MemCbImpl<TObject, TReturnType, TArgType const &, 2, TExtraArgs>
	{
		typedef TReturnType (TObject::*Function)(TArgType const &, TArgType const &, TExtraArgs const &);

		TObject &d_object;
		Function d_function;
		TExtraArgs const &d_args;

		public:
			MemCbImpl(TObject &object, Function function, TExtraArgs const &args);

			TReturnType operator()(TArgType const &arg1, TArgType const &arg2);
	};
	
	template <typename TObject, typename TReturnType, typename TArgType, typename TExtraArgs>
	MemCbImpl<TObject, TReturnType, TArgType const &, 2, TExtraArgs>::MemCbImpl(TObject &object, Function function, TExtraArgs const &args)
	:
		d_object(object),
		d_function(function),
		d_args(args)
	{
	}
	
	template <typename TObject, typename TReturnType, typename TArgType, typename TExtraArgs>
	TReturnType MemCbImpl<TObject, TReturnType, TArgType const &, 2, TExtraArgs>::operator()(TArgType const &arg1, TArgType const &arg2)
	{
		return (d_object.*d_function)(arg1, arg2, d_args);
	}
}
}

#endif /* __BASE_FUNCTIONAL_MEMCB_H__ */
