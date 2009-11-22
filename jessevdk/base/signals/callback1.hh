/*
 *	Callback template class for storing member function pointers
 *
 *	Author: Jesse van den Kieboom
 */
#ifndef __JESSEVDK_BASE_SIGNALS_CALLBACK1_H__
#define __JESSEVDK_BASE_SIGNALS_CALLBACK1_H__

#include <jessevdk/base/signals/callbackbase.hh>

namespace jessevdk
{
namespace base
{
namespace signals
{
	/** Class used for storing member function pointers.
	  * This class is used internally to register callbacks for a certain
	  * signal. This specialization allows callback arguments,
	  * object member functions and no user data
	  * @author Jesse van den Kieboom
	  */
	template <typename TFunction, typename TArgs, typename TObject>
	class Callback<TFunction, TArgs, TObject, _CbNone> : public CallbackBase<TArgs>
	{
		TFunction d_function;
		TObject &d_obj;

		public:
			/** Constructor.
			  * This constructor creates a new callback object for a member function
			  * pointer
			  * @param obj the callback object
			  * @param function the callback member function
			  * @param priority the callback priority
			  * @author Jesse van den Kieboom
			  */
			Callback(TObject &obj, TFunction function = 0, int priority = 0);

			/** Emit callback.
			  * This function emits (executes) the stored callback. This
			  * function always returns false in this specialization since an
			  * argument is required.
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
			virtual Callback<TFunction, TArgs, TObject> *Clone() const;

			/** Overloaded equality operator.
			  * Used to compare callbacks by means of the referenced object
			  * and member function
			  * @param other the object to compare with
			  * @return true if the callbacks store the same object/member
			  * function
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
			template <typename TOtherObject, typename TOtherArgs, typename TReturnType>
			bool EmitArg(TReturnType (TOtherObject::* const func)(TOtherArgs &), TArgs &args) const;

			template <typename TOtherObject, typename TOtherArgs, typename TReturnType>
			bool EmitArg(TReturnType (TOtherObject::* const func)(TOtherArgs), TArgs &args) const;
	};

	namespace {
		template <typename TArgs, typename TOtherArgs, typename TReturnType>
		struct CallerImplementation1
		{
		};

		template <typename TArgs, typename TOtherArgs>
		struct CallerImplementation1<TArgs, TOtherArgs, bool>
		{
			template <typename TObject, typename TOtherObject>
			static bool Caller(TObject &obj, bool (TOtherObject::* const function)(TOtherArgs &), TArgs &args)
			{
				return (obj.*function)(dynamic_cast<TOtherArgs &>(args));
			}

			template <typename TObject, typename TOtherObject>
			static bool Caller(TObject &obj, bool (TOtherObject::* const function)(TOtherArgs), TArgs &args)
			{
				TOtherArgs a = args;
				return (obj.*function)(a);
			}
		};

		template <typename TArgs>
		struct CallerImplementation1<TArgs, TArgs &, bool>
		{
			template <typename TObject, typename TOtherObject>
			static bool Caller(TObject &obj, bool (TOtherObject::* const function)(TArgs &), TArgs &args)
			{
				return (obj.*function)(args);
			}
		};

		template <typename TArgs, typename TOtherArgs>
		struct CallerImplementation1<TArgs, TOtherArgs, void>
		{
			template <typename TObject, typename TOtherObject>
			static bool Caller(TObject &obj, void (TOtherObject::* const function)(TOtherArgs &), TArgs &args)
			{
				(obj.*function)(dynamic_cast<TOtherArgs &>(args));
				return false;
			}

			template <typename TObject, typename TOtherObject>
			static bool Caller(TObject &obj, void (TOtherObject::* const function)(TOtherArgs), TArgs &args)
			{
				TOtherArgs a = args;
				(obj.*function)(a);
				return false;
			}
		};

		template <typename TArgs>
		struct CallerImplementation1<TArgs, TArgs &, void>
		{
			template <typename TObject, typename TOtherObject>
			static bool Caller(TObject &obj, void (TOtherObject::* const function)(TArgs &), TArgs &args)
			{
				(obj.*function)(args);
				return false;
			}
		};
	}

	template <typename TFunction, typename TArgs, typename TObject>
	inline Callback<TFunction, TArgs, TObject, _CbNone>::Callback(TObject &obj, TFunction function, int priority)
	:
		CallbackBase<TArgs>(priority),
		d_function(function),
		d_obj(obj)
	{
	}

	template <typename TFunction, typename TArgs, typename TObject>
	inline bool Callback<TFunction, TArgs, TObject, _CbNone>::Emit() const
	{
		return false;
	}

	template <typename TFunction, typename TArgs, typename TObject>
	inline bool Callback<TFunction, TArgs, TObject, _CbNone>::Emit(TArgs &args) const
	{
		return d_function ? EmitArg(d_function, args) : false;
	}

	template <typename TFunction, typename TArgs, typename TObject>
	inline Callback<TFunction, TArgs, TObject, _CbNone> *Callback<TFunction, TArgs, TObject, _CbNone>::Clone() const
	{
		return new Callback<TFunction, TArgs, TObject, _CbNone>(d_obj, d_function, this->Priority());
	}

	template <typename TFunction, typename TArgs, typename TObject>
	inline bool Callback<TFunction, TArgs, TObject, _CbNone>::operator==(CallbackBase<TArgs> const &other) const
	{
		try
		{
			Callback<TFunction, TArgs, TObject> const &cast = dynamic_cast<Callback<TFunction, TArgs, TObject, _CbNone> const &>(other);

			return &(cast.d_obj) == &d_obj && cast.d_function == d_function;
		}
		catch (std::bad_cast)
		{
			// Could not cast
			return false;
		}
	}

	template <typename TFunction, typename TArgs, typename TObject>
	TFunction Callback<TFunction, TArgs, TObject, _CbNone>::Function() const
	{
		return d_function;
	}

	template <typename TFunction, typename TArgs, typename TObject>
	template <typename TOtherObject, typename TOtherArgs, typename TReturnType>
	inline bool Callback<TFunction, TArgs, TObject, _CbNone>::EmitArg(TReturnType (TOtherObject::* const func)(TOtherArgs &), TArgs &args) const
	{
		return CallerImplementation1<TArgs, TOtherArgs, TReturnType>::Caller(d_obj, func, args);
	}

	template <typename TFunction, typename TArgs, typename TObject>
	template <typename TOtherObject, typename TOtherArgs, typename TReturnType>
	inline bool Callback<TFunction, TArgs, TObject, _CbNone>::EmitArg(TReturnType (TOtherObject::* const func)(TOtherArgs), TArgs &args) const
	{
		return CallerImplementation1<TArgs, TOtherArgs, TReturnType>::Caller(d_obj, func, args);
	}
}
}
}

#endif /* __JESSEVDK_BASE_SIGNALS_CALLBACK1_H__ */
