/*
 *	Callback template class for storing member function pointers
 *	
 *	Author: Jesse van den Kieboom
 */
#ifndef __BASE_SIGNALS_CALLBACK4_H__
#define __BASE_SIGNALS_CALLBACK4_H__

#include <typeinfo>
#include "Signals/CallbackBase/callbackbase.hh"

namespace base
{
namespace signals
{
	/** Class used for storing member function pointers.
	  * This class is used internally to register callbacks for a certain
	  * signal. This is a specialization used for callbacks with no arguments,
	  * an object member function and no user data
	  * @author Jesse van den Kieboom
	  */
	template <typename TFunction, typename TObject>
	class Callback<TFunction, _CbNone, TObject, _CbNone> : public CallbackBase<_CbNone>
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
			virtual Callback<TFunction, _CbNone, TObject, _CbNone> *clone() const;
			
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
		private:
			template <typename TOtherObject, typename TReturnType>
			bool emit(TReturnType (TOtherObject::* const func)()) const;
	};
	
	namespace {
		template <typename TObject, typename TReturnType>
		struct caller_implementation4
		{
		};
		
		template <typename TObject>
		struct caller_implementation4<TObject, bool>
		{
			template <typename TOtherObject>
			static bool caller(TObject &obj, bool (TObject::* const function)())
			{
				return (obj.*function)();
			}
			
			template <typename TOtherObject>
			static bool caller(TObject &obj, bool (TOtherObject::* const function)())
			{
				return (dynamic_cast<TOtherObject &>(obj).*function)();
			}
		};

		template <typename TObject>
		struct caller_implementation4<TObject, void>
		{
			template <typename TOtherObject>
			static bool caller(TObject &obj, void (TObject::* const function)())
			{
				(obj.*function)();
				return false;
			}
			
			template <typename TOtherObject>
			static bool caller(TObject &obj, void (TOtherObject::* const function)())
			{
				(dynamic_cast<TOtherObject &>(obj).*function)();
				return false;
			}
		};
	}

	template <typename TFunction, typename TObject>
	inline Callback<TFunction, _CbNone, TObject, _CbNone>::Callback(TObject &obj, TFunction function, int priority)
	:
		CallbackBase<_CbNone>(priority),
		d_function(function),
		d_obj(obj)
	{
	}
	
	template <typename TFunction, typename TObject>
	inline bool Callback<TFunction, _CbNone, TObject, _CbNone>::emit() const
	{
		return d_function ? emit(d_function) : false;
	}

	template <typename TFunction, typename TObject>
	inline bool Callback<TFunction, _CbNone, TObject, _CbNone>::emit(_CbNone &args) const
	{
		return emit();
	}
	
	template <typename TFunction, typename TObject>
	inline Callback<TFunction, _CbNone, TObject, _CbNone> *Callback<TFunction, _CbNone, TObject, _CbNone>::clone() const
	{
		return new Callback<TFunction, _CbNone, TObject, _CbNone>(d_obj, d_function, this->priority());
	}
	
	template <typename TFunction, typename TObject>
	inline bool Callback<TFunction, _CbNone, TObject, _CbNone>::operator==(CallbackBase<_CbNone> const &other) const
	{
		try
		{
			Callback<TFunction, _CbNone, TObject, _CbNone> const &cast = dynamic_cast<Callback<TFunction, _CbNone, TObject, _CbNone> const &>(other);
						
			return &(cast.d_obj) == &d_obj && cast.d_function == d_function;
		}
		catch (std::bad_cast)
		{
			// Could not cast
			return false;
		}
	}
	
	template <typename TFunction, typename TObject>
	TFunction Callback<TFunction, _CbNone, TObject, _CbNone>::function() const
	{
		return d_function;
	}
	
	template <typename TFunction, typename TObject>
	template <typename TOtherObject, typename TReturnType>
	bool Callback<TFunction, _CbNone, TObject, _CbNone>::emit(TReturnType (TOtherObject::* const func)()) const
	{
		return caller_implementation4<TObject, TReturnType>::caller(d_obj, func);
	}
}
}

#endif /* __BASE_SIGNALS_CALLBACK4_H__ */
