/*
 *	Callback template class for storing member function pointers
 *
 *	Author: Jesse van den Kieboom
 */
#ifndef __JESSEVDK_BASE_SIGNALS_CALLBACKU2_H__
#define __JESSEVDK_BASE_SIGNALS_CALLBACKU2_H__

#include <jessevdk/base/signals/callbackbase.hh>

namespace jessevdk
{
namespace base
{
namespace signals
{
	/** Class used for storing member function pointers.
	  * This class is used internally to register callbacks for a certain
	  * signal. This is a specialization used for callbacks with no arguments,
	  * has a plain C callback function and allows special user data to be
	  * provided with the emission
	  * of the callback.
	  * @author Jesse van den Kieboom
	  */
	template <typename TFunction, typename TUserData>
	class Callback<TFunction, _CbNone, _CbNone, TUserData> : public CallbackBase<_CbNone>
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
			  * This function emits (executes) the stored callback
			  * @return True to stop the signal from being emitted, false
			  * otherwise
			  * @author Jesse van den Kieboom
			  */
			virtual bool Emit() const;

			/** Emit callback.
			  * This function emits (executes) the stored callback. Since this
			  * specialization has no arguments, this will simply call the emit
			  * function without any arguments
			  * @param args the argument to be provided to the callback function.
			  *
			  * @return True to stop the signal from being emitted, false
			  * otherwise
			  * @author Jesse van den Kieboom
			  */
			virtual bool Emit(_CbNone &args) const;

			/** Clone object.
			  * Needed to allow for the cloneable pattern which prevents slicing
			  * @return A new copy of this callback
			  * @author Jesse van den Kieboom
			  */
			virtual Callback<TFunction, _CbNone, _CbNone, TUserData> *Clone() const;

			/** Overloaded equality operator.
			  * Used to compare callbacks by means of the referenced object
			  * and member function
			  * @param other the object to compare with
			  * @return true if the callbacks store the same object/member
			  * function and userdata
			  * @author Jesse van den Kieboom
			  */
			virtual bool operator==(CallbackBase<_CbNone> const &other) const;

			/** Function pointer getter.
			  * Get the function pointer associated with the callback
			  * @return the function pointer
			  * @author Jesse van den Kieboom
			  */
			virtual TFunction Function() const;
	};

	template <typename TFunction, typename TUserData>
	inline Callback<TFunction, _CbNone, _CbNone, TUserData>::Callback(TFunction function, TUserData const &userdata, int priority)
	:
		CallbackBase<_CbNone>(priority),
		d_function(function),
		d_userdata(userdata)
	{
	}

	template <typename TFunction, typename TUserData>
	inline bool Callback<TFunction, _CbNone, _CbNone, TUserData>::Emit() const
	{
		return d_function ? d_function(d_userdata) : false;
	}

	template <typename TFunction, typename TUserData>
	inline bool Callback<TFunction, _CbNone, _CbNone, TUserData>::Emit(_CbNone &args) const
	{
		return Emit();
	}

	template <typename TFunction, typename TUserData>
	inline Callback<TFunction, _CbNone, _CbNone, TUserData> *Callback<TFunction, _CbNone, _CbNone, TUserData>::Clone() const
	{
		return new Callback<TFunction, _CbNone, _CbNone, TUserData>(d_function, d_userdata, this->priority());
	}

	template <typename TFunction, typename TUserData>
	inline bool Callback<TFunction, _CbNone, _CbNone, TUserData>::operator==(CallbackBase<_CbNone> const &other) const
	{
		try
		{
			Callback<TFunction, _CbNone, _CbNone, TUserData> const &cast = dynamic_cast<Callback<TFunction, _CbNone, _CbNone, TUserData> const &>(other);

			return cast.d_function == d_function && cast.d_userdata == d_userdata;
		}
		catch (std::bad_cast)
		{
			// Could not cast
			return false;
		}
	}

	template <typename TFunction, typename TUserData>
	TFunction Callback<TFunction, _CbNone, _CbNone, TUserData>::Function() const
	{
		return d_function;
	}
}
}
}

#endif /* __JESSEVDK_BASE_SIGNALS_CALLBACKU2_H__ */
