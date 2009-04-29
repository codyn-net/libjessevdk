/*
 *	Callback template class for storing member function pointers
 *	
 *	Author: Jesse van den Kieboom
 */
#ifndef __BASE_SIGNALS_CALLBACKU4_H__
#define __BASE_SIGNALS_CALLBACKU4_H__

#include "Signals/CallbackBase/callbackbase.hh"

namespace base
{
namespace signals
{
	/** Class used for storing member function pointers.
	  * This class is used internally to register callbacks for a certain
	  * signal. This is a specialization used for callbacks with no arguments
	  * has an object member function callback and allows special user data to 
	  * be provided with the emission
	  * of the callback.
	  * @author Jesse van den Kieboom
	  */
	template <typename TFunction, typename TObject, typename TUserData>
	class Callback<TFunction, _CbNone, TObject, TUserData> : public CallbackBase<_CbNone>
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
			  * This function emits (executes) the stored callback
			  * @return True to stop the signal from being emitted, false 
			  * otherwise
			  * @author Jesse van den Kieboom
			  */ 
			virtual bool emit() const;
			
			/** Emit callback.
			  * This function emits (executes) the stored callback. Since this 
			  * specialization has no arguments, this will simply call the emit 
			  * function without any arguments
			  * @param args the argument to be provided to the callback function
			  * @return True to stop the signal from being emitted, false 
			  * otherwise
			  * @author Jesse van den Kieboom
			  */ 
			virtual bool emit(_CbNone &args) const;
			
			/** Clone object.
			  * Needed to allow for the cloneable pattern which prevents slicing
			  * @return A new copy of this callback
			  * @author Jesse van den Kieboom
			  */
			virtual Callback<TFunction, _CbNone, TObject, TUserData> *clone() const;
			
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
			virtual TFunction function() const;
	};

	template <typename TFunction, typename TObject, typename TUserData>
	inline Callback<TFunction, _CbNone, TObject, TUserData>::Callback(TObject &obj, TFunction function, TUserData const &userdata, int priority)
	:
		CallbackBase<_CbNone>(priority),
		d_function(function),
		d_obj(obj),
		d_userdata(userdata)
	{
	}
	
	template <typename TFunction, typename TObject, typename TUserData>
	inline bool Callback<TFunction, _CbNone, TObject, TUserData>::emit() const
	{
		return d_function ? (d_obj.*d_function)(d_userdata) : false;
	}

	template <typename TFunction, typename TObject, typename TUserData>
	inline bool Callback<TFunction, _CbNone, TObject, TUserData>::emit(_CbNone &args) const
	{
		return emit();
	}
	
	template <typename TFunction, typename TObject, typename TUserData>
	inline Callback<TFunction, _CbNone, TObject, TUserData> *Callback<TFunction, _CbNone, TObject, TUserData>::clone() const
	{
		return new Callback<TFunction, _CbNone, TObject, TUserData>(d_obj, d_function, d_userdata, this->priority());
	}
	
	template <typename TFunction, typename TObject, typename TUserData>
	inline bool Callback<TFunction, _CbNone, TObject, TUserData>::operator==(CallbackBase<_CbNone> const &other) const
	{
		try
		{
			Callback<TFunction, _CbNone, TObject, TUserData> const &cast = dynamic_cast<Callback<TFunction, _CbNone, TObject, TUserData> const &>(other);
						
			return &(cast.d_obj) == &d_obj && cast.d_function == d_function && cast.d_userdata == d_userdata;
		}
		catch (std::bad_cast)
		{
			// Could not cast
			return false;
		}
	}
	
	template <typename TFunction, typename TObject, typename TUserData>
	TFunction Callback<TFunction, _CbNone, TObject, TUserData>::function() const
	{
		return d_function;
	}
}
}

#endif /* __BASE_SIGNALS_CALLBACKU4_H__ */
