/*
 *	Callback base template class for storing member function pointers
 *	
 *	Author: Jesse van den Kieboom
 */
#ifndef __BASE_SIGNALS_CALLBACK_BASE_H__
#define __BASE_SIGNALS_CALLBACK_BASE_H__

namespace base
{
namespace signals
{
	class _CbNone
	{
	};

	/** Abstract callback base class.
	  * This base class is used to be able to store template callback
	  * classes in for instance a container
	  * @author Jesse van den Kieboom
	  */
	template <typename TArgs = _CbNone>
	class CallbackBase
	{
		int d_priority;
		
		public:			
			/** Default constructor
			  * @param priority the callback priority
			  * @author Jesse van den Kieboom
			  */
			CallbackBase(int priority = 0);

			/** Destructor.
			  * @author Jesse van den Kieboom
			  */
			virtual ~CallbackBase() {};
			
			/** Emit callback.
			  * This function emits (executes) the stored callback
			  * @return True to stop the signal from being emitted, false 
			  * otherwise
			  * @author Jesse van den Kieboom
			  */
			virtual bool emit() const = 0;
			
			/** Emit callback.
			  * This function emits (executes) the stored callback
			  * @param args the argument to be provided to the callback function
			  * @return True to stop the signal from being emitted, false 
			  * otherwise
			  * @author Jesse van den Kieboom
			  */
			virtual bool emit(TArgs &args) const = 0;
			
			/** Clone object.
			  * Needed to allow for the cloneable pattern which prevents slicing
			  * @return A new copy of this callback
			  * @author Jesse van den Kieboom
			  */
			virtual CallbackBase<TArgs> *clone() const = 0;
			
			/** Overloaded equality operator.
			  * Used to compare callbacks by means of its data (callback 
			  * function, optional object data or user data)
			  * @param other the object to compare with
			  * @return true if the callbacks store the same data
			  * @author Jesse van den Kieboom
			  */
			virtual bool operator==(CallbackBase<TArgs> const &other) const = 0;
			
			/** Get the callback priority
			  * @return the priority of the callback
			  * @author Jesse van den Kieboom
			  */
			virtual int priority() const;
			
			/** Set the callback priority
			  * @param priority the priority of the callback
			  * @author Jesse van den Kieboom
			  */
			virtual void setPriority(int priority);

			/** Comparison operator.
			  * This orders a callback from highest to lowest priority
			  * @param other the callback to compare with
			  * @return true if this has a higher priority than other
			  * @author Jesse van den Kieboom
			  */
			bool operator>(CallbackBase<TArgs> const &other) const;
	};
	
	template <typename TArgs>
	inline CallbackBase<TArgs>::CallbackBase(int priority)
	:
		d_priority(priority)
	{
	}

	template <typename TArgs>
	inline int CallbackBase<TArgs>::priority() const
	{
		return d_priority;
	}
	
	template <typename TArgs>
	inline void CallbackBase<TArgs>::setPriority(int priority)
	{
		d_priority = priority;
	}
	
	template <typename TArgs>
	bool CallbackBase<TArgs>::operator>(CallbackBase<TArgs> const &other) const
	{
		return d_priority > other.priority();
	}
}
}

#endif /* __BASE_SIGNALS_CALLBACK_BASE_H__ */

