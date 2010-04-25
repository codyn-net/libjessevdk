#ifndef __JESSEVDK_BASE_SIGNALS_CREATE_H__
#define __JESSEVDK_BASE_SIGNALS_CREATE_H__

#include <jessevdk/base/signals/callback.hh>

namespace jessevdk
{
namespace base
{
namespace signals
{
	template <typename TArgs>
	class Create
	{
		public:
			template <typename TFunction>
			static Cloneable<CallbackBase<TArgs> > Callback(TFunction function)
			{
				return jessevdk::base::signals::Callback<TFunction, TArgs>(function, 0);
			}

			template <typename TFunction, typename TUserData>
			static Cloneable<CallbackBase<TArgs> > Callback(TFunction function, TUserData const &data)
			{
				return jessevdk::base::signals::Callback<TFunction, TArgs, _CbNone, TUserData>(function, data, 0);
			}

			template <typename TObject, typename TReturnType, typename TOtherObject, typename TOtherArgs>
			static Cloneable<CallbackBase<TArgs> > Callback(TObject &obj, TReturnType (TOtherObject::* const function)(TOtherArgs))
			{
				return CreateCallback(dynamic_cast<TOtherObject &>(obj), function);
			}

			template <typename TObject, typename TReturnType, typename TOtherObject>
			static Cloneable<CallbackBase<TArgs> > Callback(TObject &obj, TReturnType (TOtherObject::* const function)())
			{
				return CreateCallback(dynamic_cast<TOtherObject &>(obj), function);
			}

			template <typename TObject, typename TReturnType, typename TOtherObject, typename TOtherUserData, typename TUserData>
			static Cloneable<CallbackBase<TArgs> > Callback(TObject &obj, TReturnType (TOtherObject::* const function)(TOtherUserData), TUserData const &data)
			{
				return CreateCallback(dynamic_cast<TOtherObject &>(obj), function, data);
			}

			template <typename TObject, typename TReturnType, typename TOtherObject, typename TOtherArgs, typename TOtherUserData, typename TUserData>
			static Cloneable<CallbackBase<TArgs> > Callback(TObject &obj, TReturnType (TOtherObject::* const function)(TOtherArgs, TOtherUserData), TUserData const &data)
			{
				return CreateCallback(dynamic_cast<TOtherObject &>(obj), function, data);
			}
		private:
			template <typename TObject, typename TFunction>
			static Cloneable<CallbackBase<TArgs> > CreateCallback(TObject &obj, TFunction function)
			{
				return jessevdk::base::signals::Callback<TFunction, TArgs, TObject>(obj, function, 0);
			}

			template <typename TObject, typename TFunction, typename TUserData>
			static Cloneable<CallbackBase<TArgs> > CreateCallback(TObject &obj, TFunction function, TUserData const &data)
			{
				return jessevdk::base::signals::Callback<TFunction, TArgs, TObject, TUserData>(obj, function, data, 0);
			}
	};
}
}
}

#endif /* __JESSEVDK_BASE_SIGNALS_CREATE_H__ */

