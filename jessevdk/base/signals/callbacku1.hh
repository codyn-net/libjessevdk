/*
 *	Callback template class for storing member function pointers
 *
 *	Author: Jesse van den Kieboom
 */
#ifndef __JESSEVDK_BASE_SIGNALS_CALLBACKU1_H__
#define __JESSEVDK_BASE_SIGNALS_CALLBACKU1_H__

#include <typeinfo>
#include <jessevdk/base/signals/callbackbase.hh>
#include <iostream>

namespace jessevdk
{
namespace base
{
namespace signals
{
	/** Class used for storing member function pointers.
	  * This class is used internally to register callbacks for a certain
	  * signal. This specialization allows no arguments, has a plain C callback
	  * function and allows special user data to be provided with the emission
	  * of the callback.
	  * @author Jesse van den Kieboom
	  */
	template <typename TFunction, typename TArgs = _CbNone, typename TObject = _CbNone, typename TUserData = _CbNone>
	class Callback : public CallbackBase<TArgs>
	{
		TFunction d_function;
		TObject &d_obj;
		TUserData d_userdata;

		public:
			/** Constructor.
			  * This constructor creates a new callback object for a member function
			  * pointer
			  * @param obj the callback object
			  * @param function the callback member function
			  * @param userdata the userdata provided to the callback function on emission
			  * @param priority the callback priority
			  * @author Jesse van den Kieboom
			  */
			Callback(TObject &obj, TFunction function, TUserData const &userdata, int priority = 0);

			/** Emit callback.
			  * This function emits (executes) the stored callback. Since this
			  * specialization requires an argument, this function always
			  * returns false
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
			virtual Callback<TFunction, TArgs, TObject, TUserData> *Clone() const;

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
			bool EmitArg(TReturnType (TObject::* const func)(TOtherArgs, TUserData), TArgs &args) const;

			template <typename TOtherArgs, typename TReturnType>
			bool EmitArg(TReturnType (TObject::* const func)(TOtherArgs &, TUserData), TArgs &args) const;

			template <typename TOtherArgs, typename TReturnType>
			bool EmitArg(TReturnType (TObject::* const func)(TOtherArgs const &, TUserData), TArgs &args) const;


			template <typename TOtherArgs, typename TReturnType>
			bool EmitArg(TReturnType (TObject::* const func)(TOtherArgs, TUserData &), TArgs &args) const;

			template <typename TOtherArgs, typename TReturnType>
			bool EmitArg(TReturnType (TObject::* const func)(TOtherArgs &, TUserData &), TArgs &args) const;

			template <typename TOtherArgs, typename TReturnType>
			bool EmitArg(TReturnType (TObject::* const func)(TOtherArgs const &, TUserData &), TArgs &args) const;


			template <typename TOtherArgs, typename TReturnType>
			bool EmitArg(TReturnType (TObject::* const func)(TOtherArgs, TUserData const &), TArgs &args) const;

			template <typename TOtherArgs, typename TReturnType>
			bool EmitArg(TReturnType (TObject::* const func)(TOtherArgs &, TUserData const &), TArgs &args) const;

			template <typename TOtherArgs, typename TReturnType>
			bool EmitArg(TReturnType (TObject::* const func)(TOtherArgs const &, TUserData const &), TArgs &args) const;
	};

	namespace {
		template <typename TObject, typename TArgs, typename TOtherArgs>
		struct CallerImplementation1u
		{
			template <typename TUserData>
			static bool Caller(TObject &obj, bool (TObject::* const function)(TOtherArgs, TUserData), TUserData const &data, TArgs &args)
			{
				TOtherArgs &a(dynamic_cast<TOtherArgs &>(args));
				return (obj.*function)(a, data);
			}

			template <typename TUserData>
			static bool Caller(TObject &obj, bool (TObject::* const function)(TOtherArgs &, TUserData), TUserData const &data, TArgs &args)
			{
				return (obj.*function)(dynamic_cast<TOtherArgs &>(args), data);
			}

			template <typename TUserData>
			static bool Caller(TObject &obj, bool (TObject::* const function)(TOtherArgs const &, TUserData), TUserData const &data, TArgs &args)
			{
				return (obj.*function)(dynamic_cast<TOtherArgs const &>(args), data);
			}



			template <typename TUserData>
			static bool Caller(TObject &obj, bool (TObject::* const function)(TOtherArgs, TUserData const &), TUserData const &data, TArgs &args)
			{
				TOtherArgs &a(dynamic_cast<TOtherArgs &>(args));
				return (obj.*function)(a, data);
			}

			template <typename TUserData>
			static bool Caller(TObject &obj, bool (TObject::* const function)(TOtherArgs &, TUserData const &), TUserData const &data, TArgs &args)
			{
				return (obj.*function)(dynamic_cast<TOtherArgs &>(args), data);
			}

			template <typename TUserData>
			static bool Caller(TObject &obj, bool (TObject::* const function)(TOtherArgs const &, TUserData const &), TUserData const &data, TArgs &args)
			{
				return (obj.*function)(dynamic_cast<TOtherArgs const &>(args), data);
			}



			template <typename TUserData>
			static bool Caller(TObject &obj, bool (TObject::* const function)(TOtherArgs, TUserData &), TUserData &data, TArgs &args)
			{
				TOtherArgs &a(dynamic_cast<TOtherArgs &>(args));
				return (obj.*function)(a, data);
			}

			template <typename TUserData>
			static bool Caller(TObject &obj, bool (TObject::* const function)(TOtherArgs &, TUserData &), TUserData &data, TArgs &args)
			{
				return (obj.*function)(dynamic_cast<TOtherArgs &>(args), data);
			}

			template <typename TUserData>
			static bool Caller(TObject &obj, bool (TObject::* const function)(TOtherArgs const &, TUserData &), TUserData &data, TArgs &args)
			{
				return (obj.*function)(dynamic_cast<TOtherArgs const &>(args), data);
			}



			template <typename TUserData>
			static bool Caller(TObject &obj, void (TObject::* const function)(TOtherArgs, TUserData const &), TUserData const &data, TArgs &args)
			{
				TOtherArgs &a(dynamic_cast<TOtherArgs &>(args));
				(obj.*function)(a, data);
				return false;
			}

			template <typename TUserData>
			static bool Caller(TObject &obj, void (TObject::* const function)(TOtherArgs &, TUserData const &), TUserData const &data, TArgs &args)
			{
				(obj.*function)(dynamic_cast<TOtherArgs &>(args), data);
				return false;
			}

			template <typename TUserData>
			static bool Caller(TObject &obj, void (TObject::* const function)(TOtherArgs const &, TUserData const &), TUserData const &data, TArgs &args)
			{
				(obj.*function)(dynamic_cast<TOtherArgs const &>(args), data);
				return false;
			}



			template <typename TUserData>
			static bool Caller(TObject &obj, void (TObject::* const function)(TOtherArgs, TUserData &), TUserData &data, TArgs &args)
			{
				TOtherArgs &a(dynamic_cast<TOtherArgs &>(args));
				(obj.*function)(a, data);
				return false;
			}

			template <typename TUserData>
			static bool Caller(TObject &obj, void (TObject::* const function)(TOtherArgs &, TUserData &), TUserData &data, TArgs &args)
			{
				(obj.*function)(dynamic_cast<TOtherArgs &>(args), data);
				return false;
			}

			template <typename TUserData>
			static bool Caller(TObject &obj, void (TObject::* const function)(TOtherArgs const &, TUserData &), TUserData &data, TArgs &args)
			{
				(obj.*function)(dynamic_cast<TOtherArgs const &>(args), data);
				return false;
			}



			template <typename TUserData>
			static bool Caller(TObject &obj, void (TObject::* const function)(TOtherArgs, TUserData), TUserData const &data, TArgs &args)
			{
				TOtherArgs &a(dynamic_cast<TOtherArgs &>(args));
				(obj.*function)(a, data);
				return false;
			}

			template <typename TUserData>
			static bool Caller(TObject &obj, void (TObject::* const function)(TOtherArgs &, TUserData), TUserData const &data, TArgs &args)
			{
				(obj.*function)(dynamic_cast<TOtherArgs &>(args), data);
				return false;
			}

			template <typename TUserData>
			static bool Caller(TObject &obj, void (TObject::* const function)(TOtherArgs const &, TUserData), TUserData const &data, TArgs &args)
			{
				(obj.*function)(dynamic_cast<TOtherArgs const &>(args), data);
				return false;
			}
		};

		template <typename TObject, typename TArgs>
		struct CallerImplementation1u<TObject, TArgs, TArgs>
		{
			template <typename TUserData>
			static bool Caller(TObject &obj, bool (TObject::* const function)(TArgs, TUserData const &), TUserData const &data, TArgs &args)
			{
				return (obj.*function)(args, data);
			}

			template <typename TUserData>
			static bool Caller(TObject &obj, bool (TObject::* const function)(TArgs &, TUserData const &), TUserData const &data, TArgs &args)
			{
				return (obj.*function)(args, data);
			}

			template <typename TUserData>
			static bool Caller(TObject &obj, bool (TObject::* const function)(TArgs const &, TUserData const &), TUserData const &data, TArgs &args)
			{
				return (obj.*function)(args, data);
			}


			template <typename TUserData>
			static bool Caller(TObject &obj, bool (TObject::* const function)(TArgs, TUserData &), TUserData &data, TArgs &args)
			{
				return (obj.*function)(args, data);
			}

			template <typename TUserData>
			static bool Caller(TObject &obj, bool (TObject::* const function)(TArgs &, TUserData &), TUserData &data, TArgs &args)
			{
				return (obj.*function)(args, data);
			}

			template <typename TUserData>
			static bool Caller(TObject &obj, bool (TObject::* const function)(TArgs const &, TUserData &), TUserData &data, TArgs &args)
			{
				return (obj.*function)(args, data);
			}


			template <typename TUserData>
			static bool Caller(TObject &obj, bool (TObject::* const function)(TArgs, TUserData), TUserData const &data, TArgs &args)
			{
				return (obj.*function)(args, data);
			}

			template <typename TUserData>
			static bool Caller(TObject &obj, bool (TObject::* const function)(TArgs &, TUserData), TUserData const &data, TArgs &args)
			{
				return (obj.*function)(args, data);
			}

			template <typename TUserData>
			static bool Caller(TObject &obj, bool (TObject::* const function)(TArgs const &, TUserData), TUserData const &data, TArgs &args)
			{
				return (obj.*function)(args, data);
			}


			template <typename TUserData>
			static bool Caller(TObject &obj, void (TObject::* const function)(TArgs, TUserData const &), TUserData const &data, TArgs &args)
			{
				(obj.*function)(args, data);
				return false;
			}

			template <typename TUserData>
			static bool Caller(TObject &obj, void (TObject::* const function)(TArgs &, TUserData const &), TUserData const &data, TArgs &args)
			{
				(obj.*function)(args, data);
				return false;
			}

			template <typename TUserData>
			static bool Caller(TObject &obj, void (TObject::* const function)(TArgs const &, TUserData const &), TUserData const &data, TArgs &args)
			{
				(obj.*function)(args, data);
				return false;
			}


			template <typename TUserData>
			static bool Caller(TObject &obj, void (TObject::* const function)(TArgs, TUserData &), TUserData &data, TArgs &args)
			{
				(obj.*function)(args, data);
				return false;
			}

			template <typename TUserData>
			static bool Caller(TObject &obj, void (TObject::* const function)(TArgs &, TUserData &), TUserData &data, TArgs &args)
			{
				(obj.*function)(args, data);
				return false;
			}

			template <typename TUserData>
			static bool Caller(TObject &obj, void (TObject::* const function)(TArgs const &, TUserData &), TUserData &data, TArgs &args)
			{
				(obj.*function)(args, data);
				return false;
			}


			template <typename TUserData>
			static bool Caller(TObject &obj, void (TObject::* const function)(TArgs, TUserData), TUserData const &data, TArgs &args)
			{
				(obj.*function)(args, data);
				return false;
			}

			template <typename TUserData>
			static bool Caller(TObject &obj, void (TObject::* const function)(TArgs &, TUserData), TUserData const &data, TArgs &args)
			{
				(obj.*function)(args, data);
				return false;
			}

			template <typename TUserData>
			static bool Caller(TObject &obj, void (TObject::* const function)(TArgs const &, TUserData), TUserData const &data, TArgs &args)
			{
				(obj.*function)(args, data);
				return false;
			}
		};
	}

	template <typename TFunction, typename TArgs, typename TObject, typename TUserData>
	inline Callback<TFunction, TArgs, TObject, TUserData>::Callback(TObject &obj, TFunction function, TUserData const &userdata, int priority)
	:
		CallbackBase<TArgs>(priority),
		d_function(function),
		d_obj(obj),
		d_userdata(userdata)
	{
	}

	template <typename TFunction, typename TArgs, typename TObject, typename TUserData>
	inline bool Callback<TFunction, TArgs, TObject, TUserData>::Emit() const
	{
		return false;
	}

	template <typename TFunction, typename TArgs, typename TObject, typename TUserData>
	inline bool Callback<TFunction, TArgs, TObject, TUserData>::Emit(TArgs &args) const
	{
		return d_function ? EmitArg(d_function, args) : false;
	}

	template <typename TFunction, typename TArgs, typename TObject, typename TUserData>
	inline Callback<TFunction, TArgs, TObject, TUserData> *Callback<TFunction, TArgs, TObject, TUserData>::Clone() const
	{
		return new Callback<TFunction, TArgs, TObject, TUserData>(d_obj, d_function, d_userdata, this->Priority());
	}

	template <typename TFunction, typename TArgs, typename TObject, typename TUserData>
	inline bool Callback<TFunction, TArgs, TObject, TUserData>::operator==(CallbackBase<TArgs> const &other) const
	{
		try
		{
			Callback<TFunction, TArgs, TObject, TUserData> const &cast = dynamic_cast<Callback<TFunction, TArgs, TObject, TUserData> const &>(other);

			return &(cast.d_obj) == &d_obj && cast.d_function == d_function && cast.d_userdata == d_userdata;
		}
		catch (std::bad_cast)
		{
			// Could not cast
			return false;
		}
	}

	template <typename TFunction, typename TArgs, typename TObject, typename TUserData>
	TFunction Callback<TFunction, TArgs, TObject, TUserData>::Function() const
	{
		return d_function;
	}

	template <typename TFunction, typename TArgs, typename TObject, typename TUserData>
	template <typename TOtherArgs, typename TReturnType>
	inline bool Callback<TFunction, TArgs, TObject, TUserData>::EmitArg(TReturnType (TObject::* const func)(TOtherArgs, TUserData), TArgs &args) const
	{
		return CallerImplementation1u<TObject, TArgs, TOtherArgs>::Caller(d_obj, func, d_userdata, args);
	}

	template <typename TFunction, typename TArgs, typename TObject, typename TUserData>
	template <typename TOtherArgs, typename TReturnType>
	inline bool Callback<TFunction, TArgs, TObject, TUserData>::EmitArg(TReturnType (TObject::* const func)(TOtherArgs &, TUserData), TArgs &args) const
	{
		return CallerImplementation1u<TObject, TArgs, TOtherArgs>::Caller(d_obj, func, d_userdata, args);
	}

	template <typename TFunction, typename TArgs, typename TObject, typename TUserData>
	template <typename TOtherArgs, typename TReturnType>
	inline bool Callback<TFunction, TArgs, TObject, TUserData>::EmitArg(TReturnType (TObject::* const func)(TOtherArgs const &, TUserData), TArgs &args) const
	{
		return CallerImplementation1u<TObject, TArgs, TOtherArgs>::Caller(d_obj, func, d_userdata, args);
	}



	template <typename TFunction, typename TArgs, typename TObject, typename TUserData>
	template <typename TOtherArgs, typename TReturnType>
	inline bool Callback<TFunction, TArgs, TObject, TUserData>::EmitArg(TReturnType (TObject::* const func)(TOtherArgs, TUserData const &), TArgs &args) const
	{
		return CallerImplementation1u<TObject, TArgs, TOtherArgs>::Caller(d_obj, func, d_userdata, args);
	}

	template <typename TFunction, typename TArgs, typename TObject, typename TUserData>
	template <typename TOtherArgs, typename TReturnType>
	inline bool Callback<TFunction, TArgs, TObject, TUserData>::EmitArg(TReturnType (TObject::* const func)(TOtherArgs &, TUserData const &), TArgs &args) const
	{
		return CallerImplementation1u<TObject, TArgs, TOtherArgs>::Caller(d_obj, func, d_userdata, args);
	}

	template <typename TFunction, typename TArgs, typename TObject, typename TUserData>
	template <typename TOtherArgs, typename TReturnType>
	inline bool Callback<TFunction, TArgs, TObject, TUserData>::EmitArg(TReturnType (TObject::* const func)(TOtherArgs const &, TUserData const &), TArgs &args) const
	{
		return CallerImplementation1u<TObject, TArgs, TOtherArgs>::Caller(d_obj, func, d_userdata, args);
	}



	template <typename TFunction, typename TArgs, typename TObject, typename TUserData>
	template <typename TOtherArgs, typename TReturnType>
	inline bool Callback<TFunction, TArgs, TObject, TUserData>::EmitArg(TReturnType (TObject::* const func)(TOtherArgs, TUserData &), TArgs &args) const
	{
		return CallerImplementation1u<TObject, TArgs, TOtherArgs>::Caller(d_obj, func, const_cast<TUserData &>(d_userdata), args);
	}

	template <typename TFunction, typename TArgs, typename TObject, typename TUserData>
	template <typename TOtherArgs, typename TReturnType>
	inline bool Callback<TFunction, TArgs, TObject, TUserData>::EmitArg(TReturnType (TObject::* const func)(TOtherArgs &, TUserData &), TArgs &args) const
	{
		return CallerImplementation1u<TObject, TArgs, TOtherArgs>::Caller(d_obj, func, const_cast<TUserData &>(d_userdata), args);
	}

	template <typename TFunction, typename TArgs, typename TObject, typename TUserData>
	template <typename TOtherArgs, typename TReturnType>
	inline bool Callback<TFunction, TArgs, TObject, TUserData>::EmitArg(TReturnType (TObject::* const func)(TOtherArgs const &, TUserData &), TArgs &args) const
	{
		return CallerImplementation1u<TObject, TArgs, TOtherArgs>::Caller(d_obj, func, const_cast<TUserData &>(d_userdata), args);
	}
}
}
}

#endif /* __JESSEVDK_BASE_SIGNALS_CALLBACKU1_H__ */
