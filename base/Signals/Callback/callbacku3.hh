/*
 *	Callback template class for storing member function pointers
 *	
 *	Author: Jesse van den Kieboom
 */
#ifndef __BASE_SIGNALS_CALLBACKU3_H__
#define __BASE_SIGNALS_CALLBACKU3_H__

#include "Signals/CallbackBase/callbackbase.hh"

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
		TUserData &d_userdata;
	
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
			virtual Callback<TFunction, TArgs, _CbNone, TUserData> *clone() const;
			
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
			virtual TFunction function() const;
		private:
			template <typename TOtherArgs>
			bool emitArg(bool (* const func)(TOtherArgs &, TUserData &), TArgs &args) const;
			
			template <typename TOtherArgs>
			bool emitArg(bool (* const func)(TOtherArgs, TUserData &), TArgs &args) const;
	};
	
	namespace {
		template <typename TArgs, typename TOtherArgs>
		struct caller_implementation3u
		{			
			template <typename TUserData>
			static bool caller(bool (* const function)(TOtherArgs &, TUserData &), TUserData &data, TArgs &args)
			{
				return (*function)(dynamic_cast<TOtherArgs &>(args), data);
			}

			template <typename TUserData>
			static bool caller(bool (* const function)(TOtherArgs, TUserData &), TUserData &data, TArgs &args)
			{
				TOtherArgs a = args;
				return (*function)(a, data);
			}
		};
		
		template <typename TArgs>
		struct caller_implementation3u<TArgs, TArgs &>
		{
			template <typename TUserData>
			static bool caller(bool (* const function)(TArgs &, TUserData &), TUserData &data, TArgs &args)
			{
				return (*function)(args, data);
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
	inline bool Callback<TFunction, TArgs, _CbNone, TUserData>::emit() const
	{
		return false;
	}

	template <typename TFunction, typename TArgs, typename TUserData>
	inline bool Callback<TFunction, TArgs, _CbNone, TUserData>::emit(TArgs &args) const
	{
		return d_function ? emitArg(d_function, args) : false;
	}
	
	template <typename TFunction, typename TArgs, typename TUserData>
	inline Callback<TFunction, TArgs, _CbNone, TUserData> *Callback<TFunction, TArgs, _CbNone, TUserData>::clone() const
	{
		return new Callback<TFunction, TArgs, _CbNone, TUserData>(d_function, d_userdata, this->priority());
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
	TFunction Callback<TFunction, TArgs, _CbNone, TUserData>::function() const
	{
		return d_function;
	}

	template <typename TFunction, typename TArgs, typename TUserData>
	template <typename TOtherArgs>	
	inline bool Callback<TFunction, TArgs, _CbNone, TUserData>::emitArg(bool (* const func)(TOtherArgs &, TUserData &), TArgs &args) const
	{
		return caller_implementation3u<TArgs, TOtherArgs>::caller(func, d_userdata, args);
	}
	
	template <typename TFunction, typename TArgs, typename TUserData>
	template <typename TOtherArgs>
	inline bool Callback<TFunction, TArgs, _CbNone, TUserData>::emitArg(bool (* const func)(TOtherArgs, TUserData &), TArgs &args) const
	{
		return caller_implementation3u<TArgs, TOtherArgs>::caller(func, d_userdata, args);
	}
}
}

#endif /* __BASE_SIGNALS_CALLBACKU3_H__ */
