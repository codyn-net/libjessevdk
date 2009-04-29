/*
 *	Callback template class for storing member function pointers
 *	
 *	Author: Jesse van den Kieboom
 */
#ifndef __BASE_SIGNALS_CALLBACK3_H__
#define __BASE_SIGNALS_CALLBACK3_H__

#include "Signals/CallbackBase/callbackbase.hh"

namespace base
{
namespace signals
{
	/** Class used for storing member function pointers.
	  * This class is used internally to register callbacks for a certain
	  * signal. This is a specialization used for callbacks with arguments,
	  * a plain C callback function and no user data
	  * @author Jesse van den Kieboom
	  */
	template <typename TFunction, typename TArgs>
	class Callback<TFunction, TArgs, _CbNone, _CbNone> : public CallbackBase<TArgs>
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
			  * This function emits (executes) the stored callback. Since this 
			  * specialization requires an argument, this function simply returns
			  * false
			  * @return True to stop the signal from being emitted, false 
			  * otherwise
			  * @author Jesse van den Kieboom
			  */ 
			virtual bool emit() const;
			
			/** Emit callback.
			  * This function emits (executes) the stored callback
			  * @param args the argument to be provided to the callback function
			  * @return True to stop the signal from being emitted, false 
			  * otherwise
			  * @author Jesse van den Kieboom
			  */ 
			virtual bool emit(TArgs &args) const;
			
			/** Clone object.
			  * Needed to allow for the cloneable pattern which prevents slicing
			  * @return A new copy of this callback
			  * @author Jesse van den Kieboom
			  */
			virtual Callback<TFunction, TArgs, _CbNone, _CbNone> *clone() const;
			
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
			virtual TFunction function() const;
		private:
			template <typename TOtherArgs>
			bool emitArg(bool (* const func)(TOtherArgs &), TArgs &args) const;
			
			template <typename TOtherArgs>
			bool emitArg(bool (* const func)(TOtherArgs), TArgs &args) const;
	};
	
	namespace {
		template <typename TArgs, typename TOtherArgs>
		struct caller_implementation3
		{			
			static bool caller(bool (* const function)(TOtherArgs &), TArgs &args)
			{
				return (*function)(dynamic_cast<TOtherArgs &>(args));
			}

			static bool caller(bool (* const function)(TOtherArgs), TArgs &args)
			{
				TOtherArgs a = args;
				return (*function)(a);
			}
		};
		
		template <typename TArgs>
		struct caller_implementation3<TArgs, TArgs>
		{
			static bool caller(bool (* const function)(TArgs &), TArgs &args)
			{
				return (*function)(args);
			}
		};
	}

	template <typename TFunction, typename TArgs>
	inline Callback<TFunction, TArgs, _CbNone, _CbNone>::Callback(TFunction function, int priority)
	:
		CallbackBase<TArgs>(priority),
		d_function(function)
	{
	}
	
	template <typename TFunction, typename TArgs>
	inline bool Callback<TFunction, TArgs, _CbNone, _CbNone>::emit() const
	{
		return false;
	}

	template <typename TFunction, typename TArgs>
	inline bool Callback<TFunction, TArgs, _CbNone, _CbNone>::emit(TArgs &args) const
	{
		return d_function ? emitArg(d_function, args) : false;
	}
	
	template <typename TFunction, typename TArgs>
	inline Callback<TFunction, TArgs, _CbNone, _CbNone> *Callback<TFunction, TArgs, _CbNone, _CbNone>::clone() const
	{
		return new Callback<TFunction, TArgs, _CbNone, _CbNone>(d_function, this->priority());
	}
	
	template <typename TFunction, typename TArgs>
	inline bool Callback<TFunction, TArgs, _CbNone, _CbNone>::operator==(CallbackBase<TArgs> const &other) const
	{
		try
		{
			Callback<TFunction, TArgs, _CbNone, _CbNone> const &cast = dynamic_cast<Callback<TFunction, TArgs, _CbNone, _CbNone> const &>(other);
						
			return cast.d_function == d_function;
		}
		catch (std::bad_cast)
		{
			// Could not cast
			return false;
		}
	}
	
	template <typename TFunction, typename TArgs>
	TFunction Callback<TFunction, TArgs, _CbNone, _CbNone>::function() const
	{
		return d_function;
	}
	
	template <typename TFunction, typename TArgs>
	template <typename TOtherArgs>	
	inline bool Callback<TFunction, TArgs, _CbNone, _CbNone>::emitArg(bool (* const func)(TOtherArgs &), TArgs &args) const
	{
		return caller_implementation3<TArgs, TOtherArgs>::caller(func, args);
	}
	
	template <typename TFunction, typename TArgs>
	template <typename TOtherArgs>	
	inline bool Callback<TFunction, TArgs, _CbNone, _CbNone>::emitArg(bool (* const func)(TOtherArgs), TArgs &args) const
	{
		return caller_implementation3<TArgs, TOtherArgs>::caller(func, args);
	}
}
}

#endif /* __BASE_SIGNALS_CALLBACK3_H__ */
