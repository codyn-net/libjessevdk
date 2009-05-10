/*
 *	Signal template class for storing callbacks for a specific callback 
 *  signature
 *	
 *	Author: Jesse van den Kieboom
 */
#ifndef __BASE_SIGNALS_SIGNAL_H__
#define __BASE_SIGNALS_SIGNAL_H__

#include <vector>
#include <algorithm>
#include <functional>

#include <base/Cloneable/cloneable.hh>
#include <base/Signals/CallbackBase/callbackbase.hh>
#include <base/Signals/Callback/callback.hh>

namespace base
{
namespace signals
{
	/** Class which stores callbacks.
	  * This class stores callbacks for a specific callback signature. It
	  * can be used to add (register) and remove (unregister) callbacks to
	  * functions which will then be called when the signal is emitted
	  * @author Jesse van den Kieboom
	  */	 
	template <typename TArgs = _CbNone>
	class Signal
	{
		typedef std::vector<Cloneable<CallbackBase<TArgs> > > CallbackVec;
		typedef typename CallbackVec::const_iterator ConstIterator;
		typedef typename CallbackVec::iterator Iterator;
	
		CallbackVec d_callbacks;
		CallbackVec d_callbacksAfter;

		bool d_blocked;
		Cloneable<CallbackBase<TArgs> > d_defaultHandler;
	
		public:
			/** Create new callback
			  * This is a convenient function to create a new callback method
			  * for a certain signal signature
			  * @param function the callback function to be executed on emission
			  * @param priority the callback priority (default 0)
			  * @return A callback object for the given function
			  * @author Jesse van den Kieboom
			  */
			template <typename TFunction>
			static Cloneable<Callback<TFunction, TArgs> > callback(TFunction function, int priority = 0);
			
			/** Create new callback
			  * This is a convenient function to create a new callback method
			  * for a certain signal signature
			  * @param obj the object on which the callback should be executed
			  * @param function the callback member method to be executed on 
			  * emission
			  * @param priority the callback priority (default 0)
			  * @return A callback object for the given object and member 
			  * function
			  * @author Jesse van den Kieboom
			  */
			template <typename TFunction, typename TObject>
			static Cloneable<Callback<TFunction, TArgs, TObject> > callback(TObject &obj, TFunction function, int priority = 0);
			
			/** Create new callback
			  * This is a convenient function to create a new callback method
			  * for a certain signal signature
			  * @param function the callback member method to be executed on 
			  * emission
			  * @param userdata the userdata to be provided to the callback 
			  * function on emission
			  * @param priority the callback priority (default 0)
			  * @return A callback object for the given function
			  * @author Jesse van den Kieboom
			  */
			template <typename TFunction, typename TUserData>
			static Cloneable<Callback<TFunction, TArgs, _CbNone, TUserData> > callbackData(TFunction function, TUserData const &userdata, int priority = 0);
			
			/** Create new callback
			  * This is a convenient function to create a new callback method
			  * for a certain signal signature
			  * @param obj the object on which the callback should be executed
			  * @param function the callback member method to be executed on 
			  * emission
			  * @param userdata the userdata to be provided to the callback 
			  * function on emission
			  * @param priority the callback priority (default 0)
			  * @return A callback object for the given object and member 
			  * function
			  * @author Jesse van den Kieboom
			  */
			template <typename TFunction, typename TObject, typename TUserData>
			static Cloneable<Callback<TFunction, TArgs, TObject, TUserData> > callbackData(TObject &obj, TFunction function, TUserData const &userdata, int priority = 0);
			
			/** Constructor.
			  * Default constructor. No default handler is registered for the
			  * signal
			  * @author Jesse van den Kieboom
			  */
			Signal();
			
			/** Copy constructor.
			  * Creates a new signal object from an existing signal object.
			  * The callbacks are explicitely _NOT_ copied because if you do
			  * then someone registering a callback on a signal can't be sure
			  * whether or not it is then the only callback it has registered.
			  * @param other the signal to copy from
			  * @author Jesse van den Kieboom
			  */
			Signal(Signal<TArgs> const &other);
			
			/** Constructor with default handler.
			  * With this constructor one can supply a default handler for the
			  * given signal which will be run as the last callback when the
			  * signal is emitted and none of the registered callbacks stop the
			  * emission by returning True (or by blocking the emission)
			  * @param function the default handler callback function
			  * @author Jesse van den Kieboom
			  */
			template <typename TFunction>
			Signal(TFunction function);
			
			/** Constructor with default handler.
			  * With this constructor one can supply a default handler for the
			  * given signal which will be run as the last callback when the
			  * signal is emitted and none of the registered callbacks stop the
			  * emission by returning True (or by blocking the emission)
			  * @param obj the object to which the signal belongs
			  * @param function the default handler callback function
			  * @author Jesse van den Kieboom
			  */
			template <typename TFunction, typename TObject>
			Signal(TObject &obj, TFunction function);
			
			/** Overloaded assignment operator
			  * Copies from an existing signal object.
			  * The callbacks are explicitely _NOT_ copied because if you do
			  * then someone registering a callback on a signal can't be sure
			  * whether or not it is then the only callback it has registered.
			  * @param other the signal to copy from
			  * @author Jesse van den Kieboom
			  */
			Signal<TArgs> &operator=(Signal<TArgs> const &other);
			
			/** Register callback.
			  * This functions registers a new callback on the signal
			  * @param function the callback function
			  * @param priority the callback priority (default 0)
			  * @author Jesse van den Kieboom
			  */
			template <typename TFunction>
			void add(TFunction function, int priority = 0);
			
			/** Register callback.
			  * This functions registers a new callback on the signal
			  * @param obj the callback object
			  * @param function the callback function
			  * @param priority the callback priority (default 0)
			  * @author Jesse van den Kieboom
			  */
			template <typename TFunction, typename TObject>
			void add(TObject &obj, TFunction function, int priority = 0);
			
			/** Register callback.
			  * This functions registers a new callback on the signal with
			  * the specified user data assigned
			  * @param function the callback function
			  * @param userdata the user data to be provided to the callback
			  * functio on emission
			  * @param priority the callback priority
			  * @author Jesse van den Kieboom
			  */
			template <typename TFunction, typename TUserData>
			void addData(TFunction function, TUserData const &userdata, int priority = 0);
			
			/** Register callback.
			  * This functions registers a new callback on the signal with
			  * the specified user data assigned
			  * @param obj the callback object
			  * @param function the callback function
			  * @param userdata the user data to be provided to the callback
			  * functio on emission
			  * @param priority the callback priority
			  * @author Jesse van den Kieboom
			  */
			template <typename TFunction, typename TObject, typename TUserData>
			void addData(TObject &obj, TFunction function, TUserData const &userdata, int priority = 0);
			
			/** Register callback.
			  * This functions registers a new callback on the signal.
			  * The callback will be called after the default handler
			  * @param function the callback function
			  * @param priority the callback priority (default 0)
			  * @author Jesse van den Kieboom
			  */
			template <typename TFunction>
			void addAfter(TFunction function, int priority = 0);
			
			/** Register callback.
			  * This functions registers a new callback on the signal.
			  * The callback will be called after the default handler
			  * @param obj the callback object
			  * @param function the callback function
			  * @param priority the callback priority (default 0)
			  * @author Jesse van den Kieboom
			  */
			template <typename TFunction, typename TObject>
			void addAfter(TObject &obj, TFunction function, int priority = 0);
			
			/** Register callback.
			  * This functions registers a new callback on the signal with
			  * the specified user data assigned. The callback will be called 
			  * after the default handler
			  * @param function the callback function
			  * @param userdata the user data to be provided to the callback
			  * functio on emission
			  * @param priority the callback priority
			  * @author Jesse van den Kieboom
			  */
			template <typename TFunction, typename TUserData>
			void addAfterData(TFunction function, TUserData const &userdata, int priority);
			
			/** Register callback.
			  * This functions registers a new callback on the signal with
			  * the specified user data assigned. The callback will be called 
			  * after the default handler
			  * @param obj the callback object
			  * @param function the callback function
			  * @param userdata the user data to be provided to the callback
			  * functio on emission
			  * @param priority the callback priority
			  * @author Jesse van den Kieboom
			  */
			template <typename TFunction, typename TObject, typename TUserData>
			void addAfterData(TObject &obj, TFunction function, TUserData const &userdata, int priority);
			
			/** Unregister callback.
			  * This functions unregisters a callback on the signal
			  * @param function the callback function
			  * @author Jesse van den Kieboom
			  */
			template <typename TFunction>
			void remove(TFunction function);

			/** Unregister callback.
			  * This functions unregisters a callback on the signal
			  * @param obj the callback object
			  * @param function the callback function
			  * @author Jesse van den Kieboom
			  */
			template <typename TFunction, typename TObject>
			void remove(TObject &obj, TFunction function);
			
			/** Unregister callback.
			  * This functions unregisters a callback on the signal
			  * @param function the callback function
			  * @param userdata the callback userdata
			  * @author Jesse van den Kieboom
			  */
			template <typename TFunction, typename TUserData>
			void removeData(TFunction function, TUserData const &userdata);

			/** Unregister callback.
			  * This functions unregisters a callback on the signal
			  * @param obj the callback object
			  * @param function the callback function
			  * @param userdata the callback userdata
			  * @author Jesse van den Kieboom
			  */
			template <typename TFunction, typename TObject, typename TUserData>
			void removeData(TObject &obj, TFunction function, TUserData const &userdata);

			/** Register callback.
			  * This operator registers a new callback on the signal
			  * @param callback the callback to register
			  * @return A reference to this object
			  * @author Jesse van den Kieboom
			  */
			Signal &operator+=(Cloneable<CallbackBase<TArgs> > const &callback);
			
			/** Unregister callback.
			  * This operator unregisters a registered callback on the signal
			  * @param callback the callback to unregister
			  * @return A reference to this object
			  * @author Jesse van den Kieboom
			  */
			Signal &operator-=(Cloneable<CallbackBase<TArgs> > const &callback);
		
			/** Emit callbacks.
			  * This function emits (executes) all registered callbacks for
			  * this signal
			  * @return true if the signal was handled, false otherwise
			  * @author Jesse van den Kieboom
			  */
			bool emit() const;
			
			/** Emit callbacks.
			  * This function emits (executes) all registered callbacks for
			  * this signal
			  * @param args the argument to be provided to the callback function
			  * @return true if the signal was handled, false otherwise
			  * @author Jesse van den Kieboom
			  */
			bool emit(TArgs &args) const;			

			/** Emit callbacks.
			  * This function emits (executes) all registered callbacks for
			  * this signal
			  * @return true if the signal was handled, false otherwise
			  * @author Jesse van den Kieboom
			  */
			bool operator()() const;
		
			/** Emit callbacks.
			  * This function emits (executes) all registered callbacks for
			  * this signal
			  * @param args the argument to be provided to the callback function
			  * @return true if the signal was handled, false otherwise
			  * @author Jesse van den Kieboom
			  */
			bool operator()(TArgs &args) const;
			
			/** Block signal.
			  * This function blocks the signal from being emitted. This way 
			  * registered callbacks will not be executed when the signal is
			  * emitted
			  * @author Jesse van den Kieboom
			  */
			void block();
			
			/** Unblock signal.
			  * This function unblocks a blocked signal so that when the signal
			  * is emitted the callbacks will be executed again
			  * @author Jesse van den Kieboom
			  */
			void unblock();
			
			/** Is the signal blocked.
			  * Returns whether or not the signal is currently blocked
			  * @return True if the signal is currently blocked, false otherwise
			  * @author Jesse van den Kieboom
			  */
			bool isBlocked() const;
			
			size_t size() const;
		private:
			void sort(CallbackVec &vec);
			bool remove(CallbackVec &vec, Cloneable<CallbackBase<TArgs> > const &callback);
			void copy(Signal<TArgs> const &other);
			
			/** Emit callbacks.
			  * This function emits (executes) all registered callbacks for
			  * a certain callback vector.
			  * @param vec the callback vector
			  * @param obj the calling object
			  * @param args the argument to be provided to the callback function
			  * @return true if the signal was handled, false otherwise
			  * @author Jesse van den Kieboom
			  */
			bool emit(CallbackVec vec, TArgs &args) const;
	};
	
	
	// Callback creators
	template <typename TArgs>
	template <typename TFunction>
	Cloneable<Callback<TFunction, TArgs> > Signal<TArgs>::callback(TFunction function, int priority)
	{
		return Callback<TFunction, TArgs>(function, priority);
	}
	
	template <typename TArgs>
	template <typename TFunction, typename TObject>
	Cloneable<Callback<TFunction, TArgs, TObject> > Signal<TArgs>::callback(TObject &obj, TFunction function, int priority)
	{
		return Callback<TFunction, TArgs, TObject>(obj, function, priority);
	}
	
	template <typename TArgs>
	template <typename TFunction, typename TUserData>
	Cloneable<Callback<TFunction, TArgs, _CbNone, TUserData> > Signal<TArgs>::callbackData(TFunction function, TUserData const &userdata, int priority)
	{
		return Callback<TFunction, TArgs, _CbNone, TUserData>(function, userdata, priority);
	}
	
	template <typename TArgs>
	template <typename TFunction, typename TObject, typename TUserData>
	Cloneable<Callback<TFunction, TArgs, TObject, TUserData> > Signal<TArgs>::callbackData(TObject &obj, TFunction function, TUserData const &userdata, int priority)
	{
		return Callback<TFunction, TArgs, TObject, TUserData>(obj, function, userdata, priority);
	}
	
	template <typename TArgs>
	Signal<TArgs>::Signal()
	:
		d_blocked(false)
	{
	}

	template <typename TArgs>
	Signal<TArgs>::Signal(Signal<TArgs> const &other)
	{
		copy(other);
	}
	
	template <typename TArgs>
	Signal<TArgs> &Signal<TArgs>::operator=(Signal<TArgs> const &other)
	{
		if (this != &other)
			copy(other);
		
		return *this;
	}
	
	// Default handlers constructors	
	template <typename TArgs>
	template <typename TFunction>
	Signal<TArgs>::Signal(TFunction function)
	:
		d_blocked(false),
		d_defaultHandler(callback(function))
	{
	}
	
	template <typename TArgs>
	template <typename TFunction, typename TObject>
	Signal<TArgs>::Signal(TObject &obj, TFunction function)
	:
		d_blocked(false),
		d_defaultHandler(callback(obj, function))
	{
	}
	
	// Adding callbacks
	template <typename TArgs>
	template <typename TFunction>
	void Signal<TArgs>::add(TFunction function, int priority)
	{
		*this += callback(function, priority);
	}
	
	template <typename TArgs>
	template <typename TFunction, typename TObject>
	void Signal<TArgs>::add(TObject &obj, TFunction function, int priority)
	{
		*this += callback(obj, function, priority);
	}
	
	template <typename TArgs>
	template <typename TFunction, typename TUserData>
	void Signal<TArgs>::addData(TFunction function, TUserData const &userdata, int priority)
	{
		*this += callbackData(function, userdata, priority);
	}
	
	template <typename TArgs>
	template <typename TFunction, typename TObject, typename TUserData>
	void Signal<TArgs>::addData(TObject &obj, TFunction function, TUserData const &userdata, int priority)
	{
		*this += callbackData(obj, function, userdata, priority);
	}
	
	template <typename TArgs>
	template <typename TFunction>
	void Signal<TArgs>::addAfter(TFunction function, int priority)
	{
		d_callbacksAfter.push_back(callback(function, priority));
		
		sort(d_callbacksAfter);
	}	
	
	template <typename TArgs>
	template <typename TFunction, typename TObject>
	void Signal<TArgs>::addAfter(TObject &obj, TFunction function, int priority)
	{
		d_callbacksAfter.push_back(callback(obj, function, priority));
		
		sort(d_callbacksAfter);
	}
	
	template <typename TArgs>
	template <typename TFunction, typename TUserData>
	void Signal<TArgs>::addAfterData(TFunction function, TUserData const &userdata, int priority)
	{
		d_callbacksAfter.push_back(callbackData(function, userdata, priority));
		
		sort(d_callbacksAfter);
	}	
	
	template <typename TArgs>
	template <typename TFunction, typename TObject, typename TUserData>
	void Signal<TArgs>::addAfterData(TObject &obj, TFunction function, TUserData const &userdata, int priority)
	{
		d_callbacksAfter.push_back(callbackData(obj, function, userdata, priority));
		
		sort(d_callbacksAfter);
	}

	template <typename TArgs>
	Signal<TArgs> &Signal<TArgs>::operator+=(Cloneable<CallbackBase<TArgs> > const &callback)
	{
		d_callbacks.push_back(callback);
		
		sort(d_callbacks);
		return *this;
	}
	
	// Removing callbacks
	template <typename TArgs>
	template <typename TFunction>
	void Signal<TArgs>::remove(TFunction function)
	{
		*this -= callback(function);
	}
	
	template <typename TArgs>
	template <typename TFunction, typename TObject>
	void Signal<TArgs>::remove(TObject &obj, TFunction function)
	{
		*this -= callback(obj, function);
	}
	
	template <typename TArgs>
	template <typename TFunction, typename TUserData>
	void Signal<TArgs>::removeData(TFunction function, TUserData const &userdata)
	{
		*this -= callbackData(function, userdata);
	}
	
	template <typename TArgs>
	template <typename TFunction, typename TObject, typename TUserData>
	void Signal<TArgs>::removeData(TObject &obj, TFunction function, TUserData const &userdata)
	{
		*this -= callbackData(obj, function, userdata);
	}
	
	template <typename TArgs>
	Signal<TArgs> &Signal<TArgs>::operator-=(Cloneable<CallbackBase<TArgs> > const &callback)
	{
		remove(d_callbacks, callback) || remove(d_callbacksAfter, callback);
		
		return *this;
	}

	template <typename TArgs>
	bool Signal<TArgs>::remove(CallbackVec &vec, Cloneable<CallbackBase<TArgs> > const &callback)
	{
		for (Iterator iter = vec.begin(); iter != vec.end(); iter++)
		{		
			if (**iter == callback)
			{
				vec.erase(iter);
				sort(vec);
				
				return true;
			}
		}
		
		return false;
	}
	
	// Emission
	template <typename TArgs>
	bool Signal<TArgs>::emit(CallbackVec vec, TArgs &args) const
	{
		for (ConstIterator iter = vec.begin(); iter != vec.end(); iter++)
			if (d_blocked || (*iter)->emit(args))
				return true;
		
		return false;
	}
	
	template <typename TArgs>
	bool Signal<TArgs>::emit() const
	{
		TArgs args;
		return emit(args);
	}

	template <typename TArgs>
	bool Signal<TArgs>::emit(TArgs &args) const
	{
		if (emit(d_callbacks, args))
			return true;
		
		if (d_blocked || (d_defaultHandler.isAssigned() && d_defaultHandler->emit(args)))
			return true;
		
		return emit(d_callbacksAfter, args);
	}
	
	template <typename TArgs>
	bool Signal<TArgs>::operator()() const
	{
		return emit();
	}

	template <typename TArgs>
	bool Signal<TArgs>::operator()(TArgs &args) const
	{
		return emit(args);
	}
	
	// Blocking	
	template <typename TArgs>
	void Signal<TArgs>::block()
	{
		d_blocked = true;
	}
	
	template <typename TArgs>
	void Signal<TArgs>::unblock()
	{
		d_blocked = false;
	}
	
	template <typename TArgs>
	bool Signal<TArgs>::isBlocked() const
	{
		return d_blocked;
	}
	
	// Sorting
	template <typename TArgs>
	void Signal<TArgs>::sort(CallbackVec &vec)
	{
		std::sort(vec.begin(), vec.end(), std::greater<Cloneable<CallbackBase<TArgs> > >());
	}
	
	// Copying
	template <typename TArgs>
	void Signal<TArgs>::copy(Signal<TArgs> const &other)
	{
		d_blocked = other.d_blocked;
		d_defaultHandler = other.d_defaultHandler;
	}
	
	template <typename TArgs>
	inline size_t Signal<TArgs>::size() const
	{
		return d_callbacks.size() + d_callbacksAfter.size();
	}
}
}

#endif /* __BASE_SIGNALS_SIGNAL_H__ */
