/*
 *	Callback template class for storing member function pointers
 *
 *	Author: Jesse van den Kieboom
 */
#ifndef __JESSEVDK_BASE_SIGNALS_CALLBACKU3_H__
#define __JESSEVDK_BASE_SIGNALS_CALLBACKU3_H__

#include <jessevdk/base/signals/callbackbase.hh>

namespace jessevdk
{
namespace base
{
namespace signals
{
	/** Class used for storing member function pointers.
	  * This class is used internally to register callbacks for a certain
	  * signal. This is a specialization used for callbacks with arguments,
	  * has a plain C callback function and allows special user data to be
	  * provided with the emission
	  * of the callback.
	  * @author Jesse van den Kieboom
	  */
	template <typename TFunction, typename TArgs, typename TUserData>
	class Callback<TFunction, TArgs, _CbNone, TUserData> : public CallbackBase<TArgs>
	{
		TFunction d_function;
		TUserData d_userdata;

		public:
			/** Constructor.
			  * This constructor creates a new callback object for a member function
			  * pointer
			  * @param function the callback member function
			  * @param userdata the userdata provided to the callback function on emission
			  * @param priority the callback priority
			  * @author Jesse van den Kieboom
			  */
			Callback(TFunction function, TUserData const &userdata, int priority = 0);

			/** Emit callback.
			  * This function emits (executes) the stored callback. Since this
			  * specialization requires an argument, this function simply returns
			  * false and further does nothing
			  * @return True to stop the signal from being emitted, false
			  * otherwise
			  * @author Jesse van den Kieboom
			  */
			virtual bool Emit() const;

			/** Emit callback.
			  * This function emits (executes) the stored callback
			  * @param args the argument to be provided to the callback function
			  * @return True to stop the signal from being emitted, false
			  * otherwise
			  * @author Jesse van den Kieboom
			  */
			virtual bool Emit(TArgs &args) const;

			/** Clone object.
			  * Needed to allow for the cloneable pattern which prevents slicing
			  * @return A new copy of this callback
			  * @author Jesse van den Kieboom
			  */
			virtual Callback<TFunction, TArgs, _CbNone, TUserData> *Clone() const;

			/** Overloaded equality operator.
			  * Used to compare callbacks by means of the referenced object
			  * and member function
			  * @param other the object to compare with
			  * @return true if the callbacks store the same object/member
			  * function and userdata
			  * @author Jesse van den Kieboom
			  */
			virtual bool operator==(CallbackBase<TArgs> const &other) const;

			/** Function pointer getter.
			  * Get the function pointer associated with the callback
			  * @return the function pointer
			  * @author Jesse van den Kieboom
			  */
			virtual TFunction Function() const;
		private:

			template <typename TOtherArgs, typename TReturnType>
			bool EmitArg(TReturnType (* const func)(TOtherArgs, TUserData), TArgs &args) const;

			template <typename TOtherArgs, typename TReturnType>
			bool EmitArg(TReturnType (* const func)(TOtherArgs &, TUserData), TArgs &args) const;

			template <typename TOtherArgs, typename TReturnType>
			bool EmitArg(TReturnType (* const func)(TOtherArgs const &, TUserData), TArgs &args) const;


			template <typename TOtherArgs, typename TReturnType>
			bool EmitArg(TReturnType (* const func)(TOtherArgs, TUserData const &), TArgs &args) const;

			template <typename TOtherArgs, typename TReturnType>
			bool EmitArg(TReturnType (* const func)(TOtherArgs &, TUserData const &), TArgs &args) const;

			template <typename TOtherArgs, typename TReturnType>
			bool EmitArg(TReturnType (* const func)(TOtherArgs const &, TUserData const &), TArgs &args) const;
	};

	namespace
	{
		template <typename TArgs, typename TOtherArgs>
		struct CallerImplementation3u
		{
			template <typename TUserData>
			static bool Caller(bool (* const function)(TOtherArgs, TUserData const &), TUserData const &data, TArgs &args)
			{
				TOtherArgs &a(dynamic_cast<TOtherArgs &>(args));
				return (*function)(a, data);
			}

			template <typename TUserData>
			static bool Caller(bool (* const function)(TOtherArgs &, TUserData const &), TUserData const &data, TArgs &args)
			{
				return (*function)(dynamic_cast<TOtherArgs &>(args), data);
			}

			template <typename TUserData>
			static bool Caller(bool (* const function)(TOtherArgs const &, TUserData const &), TUserData const &data, TArgs &args)
			{
				return (*function)(dynamic_cast<TOtherArgs const &>(args), data);
			}


			template <typename TUserData>
			static bool Caller(bool (* const function)(TOtherArgs, TUserData), TUserData const &data, TArgs &args)
			{
				TOtherArgs &a(dynamic_cast<TOtherArgs &>(args));
				return (*function)(a, data);
			}

			template <typename TUserData>
			static bool Caller(bool (* const function)(TOtherArgs &, TUserData), TUserData const &data, TArgs &args)
			{
				return (*function)(dynamic_cast<TOtherArgs &>(args), data);
			}

			template <typename TUserData>
			static bool Caller(bool (* const function)(TOtherArgs const &, TUserData), TUserData const &data, TArgs &args)
			{
				return (*function)(dynamic_cast<TOtherArgs const &>(args), data);
			}



			template <typename TUserData>
			static bool Caller(void (* const function)(TOtherArgs, TUserData const &), TUserData const &data, TArgs &args)
			{
				TOtherArgs &a(dynamic_cast<TOtherArgs &>(args));
				(*function)(a, data);
				return false;
			}

			template <typename TUserData>
			static bool Caller(void (* const function)(TOtherArgs &, TUserData const &), TUserData const &data, TArgs &args)
			{
				(*function)(dynamic_cast<TOtherArgs &>(args), data);
				return false;
			}

			template <typename TUserData>
			static bool Caller(void (* const function)(TOtherArgs const &, TUserData const &), TUserData const &data, TArgs &args)
			{
				(*function)(dynamic_cast<TOtherArgs const &>(args), data);
				return false;
			}


			template <typename TUserData>
			static bool Caller(void (* const function)(TOtherArgs, TUserData), TUserData const &data, TArgs &args)
			{
				TOtherArgs &a(dynamic_cast<TOtherArgs &>(args));
				(*function)(a, data);
				return false;
			}

			template <typename TUserData>
			static bool Caller(void (* const function)(TOtherArgs &, TUserData), TUserData const &data, TArgs &args)
			{
				(*function)(dynamic_cast<TOtherArgs &>(args), data);
				return false;
			}

			template <typename TUserData>
			static bool Caller(void (* const function)(TOtherArgs const &, TUserData), TUserData const &data, TArgs &args)
			{
				(*function)(dynamic_cast<TOtherArgs const &>(args), data);
				return false;
			}
		};

		template <typename TArgs>
		struct CallerImplementation3u<TArgs, TArgs>
		{
			template <typename TUserData>
			static bool Caller(bool (* const function)(TArgs, TUserData), TUserData const &data, TArgs &args)
			{
				return (*function)(args, data);
			}

			template <typename TUserData>
			static bool Caller(bool (* const function)(TArgs &, TUserData), TUserData const &data, TArgs &args)
			{
				return (*function)(args, data);
			}

			template <typename TUserData>
			static bool Caller(bool (* const function)(TArgs const &, TUserData), TUserData const &data, TArgs &args)
			{
				return (*function)(args, data);
			}


			template <typename TUserData>
			static bool Caller(bool (* const function)(TArgs, TUserData const &), TUserData const &data, TArgs &args)
			{
				return (*function)(args, data);
			}

			template <typename TUserData>
			static bool Caller(bool (* const function)(TArgs &, TUserData const &), TUserData const &data, TArgs &args)
			{
				return (*function)(args, data);
			}

			template <typename TUserData>
			static bool Caller(bool (* const function)(TArgs const &, TUserData const &), TUserData const &data, TArgs &args)
			{
				return (*function)(args, data);
			}



			template <typename TUserData>
			static bool Caller(void (* const function)(TArgs, TUserData), TUserData const &data, TArgs &args)
			{
				(*function)(args, data);
				return false;
			}

			template <typename TUserData>
			static bool Caller(void (* const function)(TArgs &, TUserData), TUserData const &data, TArgs &args)
			{
				(*function)(args, data);
				return false;
			}

			template <typename TUserData>
			static bool Caller(void (* const function)(TArgs const &, TUserData), TUserData const &data, TArgs &args)
			{
				(*function)(args, data);
				return false;
			}



			template <typename TUserData>
			static bool Caller(void (* const function)(TArgs, TUserData const &), TUserData const &data, TArgs &args)
			{
				(*function)(args, data);
				return false;
			}

			template <typename TUserData>
			static bool Caller(void (* const function)(TArgs &, TUserData const &), TUserData const &data, TArgs &args)
			{
				(*function)(args, data);
				return false;
			}

			template <typename TUserData>
			static bool Caller(void (* const function)(TArgs const &, TUserData const &), TUserData const &data, TArgs &args)
			{
				(*function)(args, data);
				return false;
			}
		};
	}

	template <typename TFunction, typename TArgs, typename TUserData>
	inline Callback<TFunction, TArgs, _CbNone, TUserData>::Callback(TFunction function, TUserData const &userdata, int priority)
	:
		CallbackBase<TArgs>(priority),
		d_function(function),
		d_userdata(userdata)
	{
	}

	template <typename TFunction, typename TArgs, typename TUserData>
	inline bool Callback<TFunction, TArgs, _CbNone, TUserData>::Emit() const
	{
		return false;
	}

	template <typename TFunction, typename TArgs, typename TUserData>
	inline bool Callback<TFunction, TArgs, _CbNone, TUserData>::Emit(TArgs &args) const
	{
		return d_function ? EmitArg(d_function, args) : false;
	}

	template <typename TFunction, typename TArgs, typename TUserData>
	inline Callback<TFunction, TArgs, _CbNone, TUserData> *Callback<TFunction, TArgs, _CbNone, TUserData>::Clone() const
	{
		return new Callback<TFunction, TArgs, _CbNone, TUserData>(d_function, d_userdata, this->Priority());
	}

	template <typename TFunction, typename TArgs, typename TUserData>
	inline bool Callback<TFunction, TArgs, _CbNone, TUserData>::operator==(CallbackBase<TArgs> const &other) const
	{
		try
		{
			Callback<TFunction, TArgs, _CbNone, TUserData> const &cast = dynamic_cast<Callback<TFunction, TArgs, _CbNone, TUserData> const &>(other);

			return cast.d_function == d_function && cast.d_userdata == d_userdata;
		}
		catch (std::bad_cast)
		{
			// Could not cast
			return false;
		}
	}

	template <typename TFunction, typename TArgs, typename TUserData>
	TFunction Callback<TFunction, TArgs, _CbNone, TUserData>::Function() const
	{
		return d_function;
	}

	template <typename TFunction, typename TArgs, typename TUserData>
	template <typename TOtherArgs, typename TReturnType>
	inline bool Callback<TFunction, TArgs, _CbNone, TUserData>::EmitArg(TReturnType (* const func)(TOtherArgs, TUserData), TArgs &args) const
	{
		return CallerImplementation3u<TArgs, TOtherArgs>::Caller(func, d_userdata, args);
	}

	template <typename TFunction, typename TArgs, typename TUserData>
	template <typename TOtherArgs, typename TReturnType>
	inline bool Callback<TFunction, TArgs, _CbNone, TUserData>::EmitArg(TReturnType (* const func)(TOtherArgs &, TUserData), TArgs &args) const
	{
		return CallerImplementation3u<TArgs, TOtherArgs>::Caller(func, d_userdata, args);
	}

	template <typename TFunction, typename TArgs, typename TUserData>
	template <typename TOtherArgs, typename TReturnType>
	inline bool Callback<TFunction, TArgs, _CbNone, TUserData>::EmitArg(TReturnType (* const func)(TOtherArgs const &, TUserData), TArgs &args) const
	{
		return CallerImplementation3u<TArgs, TOtherArgs>::Caller(func, d_userdata, args);
	}

	template <typename TFunction, typename TArgs, typename TUserData>
	template <typename TOtherArgs, typename TReturnType>
	inline bool Callback<TFunction, TArgs, _CbNone, TUserData>::EmitArg(TReturnType (* const func)(TOtherArgs, TUserData const &), TArgs &args) const
	{
		return CallerImplementation3u<TArgs, TOtherArgs>::Caller(func, d_userdata, args);
	}

	template <typename TFunction, typename TArgs, typename TUserData>
	template <typename TOtherArgs, typename TReturnType>
	inline bool Callback<TFunction, TArgs, _CbNone, TUserData>::EmitArg(TReturnType (* const func)(TOtherArgs &, TUserData const &), TArgs &args) const
	{
		return CallerImplementation3u<TArgs, TOtherArgs>::Caller(func, d_userdata, args);
	}

	template <typename TFunction, typename TArgs, typename TUserData>
	template <typename TOtherArgs, typename TReturnType>
	inline bool Callback<TFunction, TArgs, _CbNone, TUserData>::EmitArg(TReturnType (* const func)(TOtherArgs const &, TUserData const &), TArgs &args) const
	{
		return CallerImplementation3u<TArgs, TOtherArgs>::Caller(func, d_userdata, args);
	}
}
}
}

#endif /* __JESSEVDK_BASE_SIGNALS_CALLBACKU3_H__ */
