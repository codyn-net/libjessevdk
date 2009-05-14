#ifndef __BASE_FUNCTIONAL_H__
#define __BASE_FUNCTIONAL_H__

#include <base/Functional/memcb.hh>

namespace base
{
namespace functional
{
	template <typename TObject, typename TReturnType>
	MemCbImpl<TObject, TReturnType, int, 0, _NoneArg> memcb(TObject &object, TReturnType (TObject::*function)())
	{
		return MemCbImpl<TObject, TReturnType, int, 0, _NoneArg>(object, function);
	}
	
	template <typename TObject, typename TReturnType, typename TExtraArgs>
	MemCbImpl<TObject, TReturnType, int, 0, TExtraArgs> memcb(TObject &object, TReturnType (TObject::*function)(TExtraArgs const &), TExtraArgs const &args)
	{
		return MemCbImpl<TObject, TReturnType, int, 0, TExtraArgs>(object, function, args);
	}

	template <typename TObject, typename TReturnType, typename TArgs>
	MemCbImpl<TObject, TReturnType, TArgs const &, 1, _NoneArg> memcb(TObject &object, TReturnType (TObject::*function)(TArgs const &a1))
	{
		return MemCbImpl<TObject, TReturnType, TArgs const &, 1, _NoneArg>(object, function);
	}
	
	template <typename TObject, typename TReturnType, typename TArgs, typename TExtraArgs>
	MemCbImpl<TObject, TReturnType, TArgs const &, 1, TExtraArgs> memcb(TObject &object, TReturnType (TObject::*function)(TArgs const &a1, TExtraArgs const &), TExtraArgs const &args)
	{
		return MemCbImpl<TObject, TReturnType, TArgs const &, 1, TExtraArgs>(object, function, args);
	}
	
	template <typename TObject, typename TReturnType, typename TArgs>
	MemCbImpl<TObject, TReturnType, TArgs, 1, _NoneArg> memcb(TObject &object, TReturnType (TObject::*function)(TArgs a1))
	{
		return MemCbImpl<TObject, TReturnType, TArgs, 1, _NoneArg>(object, function);
	}
	
	template <typename TObject, typename TReturnType, typename TArgs, typename TExtraArgs>
	MemCbImpl<TObject, TReturnType, TArgs, 1, TExtraArgs> memcb(TObject &object, TReturnType (TObject::*function)(TArgs a1, TExtraArgs const &), TExtraArgs const &args)
	{
		return MemCbImpl<TObject, TReturnType, TArgs, 1, TExtraArgs>(object, function, args);
	}
	
	template <typename TObject, typename TReturnType, typename TArgs>
	MemCbImpl<TObject, TReturnType, TArgs const &, 2, _NoneArg> memcb(TObject &object, TReturnType (TObject::*function)(TArgs const &a1, TArgs const &a2))
	{
		return MemCbImpl<TObject, TReturnType, TArgs const &, 2, _NoneArg>(object, function);
	}
	
	template <typename TObject, typename TReturnType, typename TArgs, typename TExtraArgs>
	MemCbImpl<TObject, TReturnType, TArgs const &, 2, TExtraArgs> memcb(TObject &object, TReturnType (TObject::*function)(TArgs const &a1, TArgs const &a2, TExtraArgs const &), TExtraArgs const &args)
	{
		return MemCbImpl<TObject, TReturnType, TArgs const &, 2, TExtraArgs>(object, function, args);
	}
	
	template <typename TObject, typename TReturnType, typename TArgs>
	MemCbImpl<TObject, TReturnType, TArgs, 2, _NoneArg> memcb(TObject &object, TReturnType (TObject::*function)(TArgs a1, TArgs a2))
	{
		return MemCbImpl<TObject, TReturnType, TArgs, 2, _NoneArg>(object, function);
	}
	
	template <typename TObject, typename TReturnType, typename TArgs, typename TExtraArgs>
	MemCbImpl<TObject, TReturnType, TArgs, 2, TExtraArgs> memcb(TObject &object, TReturnType (TObject::*function)(TArgs a1, TArgs a2, TExtraArgs const &), TExtraArgs const &args)
	{
		return MemCbImpl<TObject, TReturnType, TArgs, 2, TExtraArgs>(object, function, args);
	}
}
}

#endif /* __BASE_FUNCTIONAL_H__ */

