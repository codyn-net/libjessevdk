/*
 *	Callback template class for storing member function pointers
 *	
 *	Author: Jesse van den Kieboom
 */
#ifndef __BASE_SIGNALS_CALLBACK2_H__
#define __BASE_SIGNALS_CALLBACK2_H__

#include "Signals/CallbackBase/callbackbase.hh"

namespace base
{
namespace signals
{
	/** Class used for storing member function pointers.
	  * This class is used internally to register callbacks for a certain
	  * signal. This is a specialization used for callbacks with no arguments,
	  * a plain C callback function and no user data
	  * @author Jesse van den Kieboom
	  */
	template <typename TFunction>
	class Callback<TFunction, _CbNone, _CbNone, _CbNone> : public CallbackBase<_CbNone>
	{
		TFunction d_function;
	
		public:
			/** Constructor.
			  * This constructor creates a new callback object for a member function
			  * pointer
			  * @param obj the callback object
			  * @param function the callback member function
			  * @param priority the callback priority
			  * @author Jesse van den Kieboom
			  */
			Callback(TFunction function = 0, int priority = 0);
		
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
			  * @param args the argument to be provided to the callback function.
			  * 
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
			virtual Callback<TFunction, _CbNone, _CbNone, _CbNone> *clone() const;
			
			/** Overloaded equality operator.
			  * Used to compare callbacks by means of the referenced object
			  * and member function
			  * @param other the object to compare with
			  * @return true if the callbacks store the same object/member
			  * function
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

	template <typename TFunction>
	inline Callback<TFunction, _CbNone, _CbNone, _CbNone>::Callback(TFunction function, int priority)
	:
		CallbackBase<_CbNone>(priority),
		d_function(function)
	{
	}
	
	template <typename TFunction>
	inline bool Callback<TFunction, _CbNone, _CbNone, _CbNone>::emit() const
	{
		return d_function ? d_function() : false;
	}

	template <typename TFunction>
	inline bool Callback<TFunction, _CbNone, _CbNone, _CbNone>::emit(_CbNone &args) const
	{
		return emit();
	}
	
	template <typename TFunction>
	inline Callback<TFunction, _CbNone, _CbNone, _CbNone> *Callback<TFunction, _CbNone, _CbNone, _CbNone>::clone() const
	{
		return new Callback<TFunction, _CbNone, _CbNone, _CbNone>(d_function, this->priority());
	}
	
	template <typename TFunction>
	inline bool Callback<TFunction, _CbNone, _CbNone, _CbNone>::operator==(CallbackBase<_CbNone> const &other) const
	{
		try
		{
			Callback<TFunction, _CbNone, _CbNone, _CbNone> const &cast = dynamic_cast<Callback<TFunction, _CbNone, _CbNone, _CbNone> const &>(other);
						
			return cast.d_function == d_function;
		}
		catch (std::bad_cast)
		{
			// Could not cast
			return false;
		}
	}
	
	template <typename TFunction>
	TFunction Callback<TFunction, _CbNone, _CbNone, _CbNone>::function() const
	{
		return d_function;
	}
}
}

#endif /* __BASE_SIGNALS_CALLBACK2_H__ */
