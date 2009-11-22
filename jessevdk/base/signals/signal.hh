/*
 *	Signal template class for storing callbacks for a specific callback
 *  signature
 *
 *	Author: Jesse van den Kieboom
 */
#ifndef __JESSEVDK_BASE_SIGNALS_SIGNAL_H__
#define __JESSEVDK_BASE_SIGNALS_SIGNAL_H__

#include <vector>
#include <algorithm>
#include <functional>

#include <jessevdk/base/cloneable.hh>
#include <jessevdk/base/signals/callbackbase.hh>
#include <jessevdk/base/signals/callback.hh>

namespace jessevdk
{
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
			static Cloneable<Callback<TFunction, TArgs> > Callback(TFunction function, int priority = 0);

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
			static Cloneable<jessevdk::base::signals::Callback<TFunction, TArgs, TObject> > Callback(TObject &obj, TFunction function, int priority = 0);

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
			static Cloneable<jessevdk::base::signals::Callback<TFunction, TArgs, _CbNone, TUserData> > CallbackData(TFunction function, TUserData const &userdata, int priority = 0);

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
			static Cloneable<jessevdk::base::signals::Callback<TFunction, TArgs, TObject, TUserData> > CallbackData(TObject &obj, TFunction function, TUserData const &userdata, int priority = 0);

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
			void Add(TFunction function, int priority = 0);

			/** Register callback.
			  * This functions registers a new callback on the signal
			  * @param obj the callback object
			  * @param function the callback function
			  * @param priority the callback priority (default 0)
			  * @author Jesse van den Kieboom
			  */
			template <typename TFunction, typename TObject>
			void Add(TObject &obj, TFunction function, int priority = 0);

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
			void AddData(TFunction function, TUserData const &userdata, int priority = 0);

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
			void AddData(TObject &obj, TFunction function, TUserData const &userdata, int priority = 0);

			/** Register callback.
			  * This functions registers a new callback on the signal.
			  * The callback will be called after the default handler
			  * @param function the callback function
			  * @param priority the callback priority (default 0)
			  * @author Jesse van den Kieboom
			  */
			template <typename TFunction>
			void AddAfter(TFunction function, int priority = 0);

			/** Register callback.
			  * This functions registers a new callback on the signal.
			  * The callback will be called after the default handler
			  * @param obj the callback object
			  * @param function the callback function
			  * @param priority the callback priority (default 0)
			  * @author Jesse van den Kieboom
			  */
			template <typename TFunction, typename TObject>
			void AddAfter(TObject &obj, TFunction function, int priority = 0);

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
			void AddAfterData(TFunction function, TUserData const &userdata, int priority);

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
			void AddAfterData(TObject &obj, TFunction function, TUserData const &userdata, int priority);

			/** Unregister callback.
			  * This functions unregisters a callback on the signal
			  * @param function the callback function
			  * @author Jesse van den Kieboom
			  */
			template <typename TFunction>
			void Remove(TFunction function);

			/** Unregister callback.
			  * This functions unregisters a callback on the signal
			  * @param obj the callback object
			  * @param function the callback function
			  * @author Jesse van den Kieboom
			  */
			template <typename TFunction, typename TObject>
			void Remove(TObject &obj, TFunction function);

			/** Unregister callback.
			  * This functions unregisters a callback on the signal
			  * @param function the callback function
			  * @param userdata the callback userdata
			  * @author Jesse van den Kieboom
			  */
			template <typename TFunction, typename TUserData>
			void RemoveData(TFunction function, TUserData const &userdata);

			/** Unregister callback.
			  * This functions unregisters a callback on the signal
			  * @param obj the callback object
			  * @param function the callback function
			  * @param userdata the callback userdata
			  * @author Jesse van den Kieboom
			  */
			template <typename TFunction, typename TObject, typename TUserData>
			void RemoveData(TObject &obj, TFunction function, TUserData const &userdata);

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
			bool Emit() const;

			/** Emit callbacks.
			  * This function emits (executes) all registered callbacks for
			  * this signal
			  * @param args the argument to be provided to the callback function
			  * @return true if the signal was handled, false otherwise
			  * @author Jesse van den Kieboom
			  */
			bool Emit(TArgs &args) const;

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
			void Block();

			/** Unblock signal.
			  * This function unblocks a blocked signal so that when the signal
			  * is emitted the callbacks will be executed again
			  * @author Jesse van den Kieboom
			  */
			void Unblock();

			/** Is the signal blocked.
			  * Returns whether or not the signal is currently blocked
			  * @return True if the signal is currently blocked, false otherwise
			  * @author Jesse van den Kieboom
			  */
			bool IsBlocked() const;

			size_t Size() const;
		private:
			void Sort(CallbackVec &vec);
			bool Remove(CallbackVec &vec, Cloneable<CallbackBase<TArgs> > const &callback);
			void Copy(Signal<TArgs> const &other);

			/** Emit callbacks.
			  * This function emits (executes) all registered callbacks for
			  * a certain callback vector.
			  * @param vec the callback vector
			  * @param obj the calling object
			  * @param args the argument to be provided to the callback function
			  * @return true if the signal was handled, false otherwise
			  * @author Jesse van den Kieboom
			  */
			bool Emit(CallbackVec vec, TArgs &args) const;
	};


	// Callback creators
	template <typename TArgs>
	template <typename TFunction>
	Cloneable<jessevdk::base::signals::Callback<TFunction, TArgs> > Signal<TArgs>::Callback(TFunction function, int priority)
	{
		return jessevdk::base::signals::Callback<TFunction, TArgs>(function, priority);
	}

	template <typename TArgs>
	template <typename TFunction, typename TObject>
	Cloneable<jessevdk::base::signals::Callback<TFunction, TArgs, TObject> > Signal<TArgs>::Callback(TObject &obj, TFunction function, int priority)
	{
		return jessevdk::base::signals::Callback<TFunction, TArgs, TObject>(obj, function, priority);
	}

	template <typename TArgs>
	template <typename TFunction, typename TUserData>
	Cloneable<jessevdk::base::signals::Callback<TFunction, TArgs, _CbNone, TUserData> > Signal<TArgs>::CallbackData(TFunction function, TUserData const &userdata, int priority)
	{
		return jessevdk::base::signals::Callback<TFunction, TArgs, _CbNone, TUserData>(function, userdata, priority);
	}

	template <typename TArgs>
	template <typename TFunction, typename TObject, typename TUserData>
	Cloneable<jessevdk::base::signals::Callback<TFunction, TArgs, TObject, TUserData> > Signal<TArgs>::CallbackData(TObject &obj, TFunction function, TUserData const &userdata, int priority)
	{
		return jessevdk::base::signals::Callback<TFunction, TArgs, TObject, TUserData>(obj, function, userdata, priority);
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
		Copy(other);
	}

	template <typename TArgs>
	Signal<TArgs> &Signal<TArgs>::operator=(Signal<TArgs> const &other)
	{
		if (this != &other)
			Copy(other);

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
	void Signal<TArgs>::Add(TFunction function, int priority)
	{
		*this += Callback(function, priority);
	}

	template <typename TArgs>
	template <typename TFunction, typename TObject>
	void Signal<TArgs>::Add(TObject &obj, TFunction function, int priority)
	{
		*this += Callback(obj, function, priority);
	}

	template <typename TArgs>
	template <typename TFunction, typename TUserData>
	void Signal<TArgs>::AddData(TFunction function, TUserData const &userdata, int priority)
	{
		*this += CallbackData(function, userdata, priority);
	}

	template <typename TArgs>
	template <typename TFunction, typename TObject, typename TUserData>
	void Signal<TArgs>::AddData(TObject &obj, TFunction function, TUserData const &userdata, int priority)
	{
		*this += CallbackData(obj, function, userdata, priority);
	}

	template <typename TArgs>
	template <typename TFunction>
	void Signal<TArgs>::AddAfter(TFunction function, int priority)
	{
		d_callbacksAfter.push_back(callback(function, priority));

		Sort(d_callbacksAfter);
	}

	template <typename TArgs>
	template <typename TFunction, typename TObject>
	void Signal<TArgs>::AddAfter(TObject &obj, TFunction function, int priority)
	{
		d_callbacksAfter.push_back(callback(obj, function, priority));

		Sort(d_callbacksAfter);
	}

	template <typename TArgs>
	template <typename TFunction, typename TUserData>
	void Signal<TArgs>::AddAfterData(TFunction function, TUserData const &userdata, int priority)
	{
		d_callbacksAfter.push_back(callbackData(function, userdata, priority));

		Sort(d_callbacksAfter);
	}

	template <typename TArgs>
	template <typename TFunction, typename TObject, typename TUserData>
	void Signal<TArgs>::AddAfterData(TObject &obj, TFunction function, TUserData const &userdata, int priority)
	{
		d_callbacksAfter.push_back(callbackData(obj, function, userdata, priority));

		Sort(d_callbacksAfter);
	}

	template <typename TArgs>
	Signal<TArgs> &Signal<TArgs>::operator+=(Cloneable<CallbackBase<TArgs> > const &callback)
	{
		d_callbacks.push_back(callback);

		Sort(d_callbacks);
		return *this;
	}

	// Removing callbacks
	template <typename TArgs>
	template <typename TFunction>
	void Signal<TArgs>::Remove(TFunction function)
	{
		*this -= Callback(function);
	}

	template <typename TArgs>
	template <typename TFunction, typename TObject>
	void Signal<TArgs>::Remove(TObject &obj, TFunction function)
	{
		*this -= Callback(obj, function);
	}

	template <typename TArgs>
	template <typename TFunction, typename TUserData>
	void Signal<TArgs>::RemoveData(TFunction function, TUserData const &userdata)
	{
		*this -= CallbackData(function, userdata);
	}

	template <typename TArgs>
	template <typename TFunction, typename TObject, typename TUserData>
	void Signal<TArgs>::RemoveData(TObject &obj, TFunction function, TUserData const &userdata)
	{
		*this -= CallbackData(obj, function, userdata);
	}

	template <typename TArgs>
	Signal<TArgs> &Signal<TArgs>::operator-=(Cloneable<CallbackBase<TArgs> > const &callback)
	{
		Remove(d_callbacks, callback) || Remove(d_callbacksAfter, callback);

		return *this;
	}

	template <typename TArgs>
	bool Signal<TArgs>::Remove(CallbackVec &vec, Cloneable<CallbackBase<TArgs> > const &callback)
	{
		for (Iterator iter = vec.begin(); iter != vec.end(); iter++)
		{
			if (**iter == callback)
			{
				vec.erase(iter);
				Sort(vec);

				return true;
			}
		}

		return false;
	}

	// Emission
	template <typename TArgs>
	bool Signal<TArgs>::Emit(CallbackVec vec, TArgs &args) const
	{
		for (ConstIterator iter = vec.begin(); iter != vec.end(); iter++)
			if (d_blocked || (*iter)->Emit(args))
				return true;

		return false;
	}

	template <typename TArgs>
	bool Signal<TArgs>::Emit() const
	{
		TArgs args;
		return Emit(args);
	}

	template <typename TArgs>
	bool Signal<TArgs>::Emit(TArgs &args) const
	{
		if (Emit(d_callbacks, args))
		{
			return true;
		}

		if (d_blocked || (d_defaultHandler.IsAssigned() && d_defaultHandler->Emit(args)))
		{
			return true;
		}

		return Emit(d_callbacksAfter, args);
	}

	template <typename TArgs>
	bool Signal<TArgs>::operator()() const
	{
		return Emit();
	}

	template <typename TArgs>
	bool Signal<TArgs>::operator()(TArgs &args) const
	{
		return Emit(args);
	}

	// Blocking
	template <typename TArgs>
	void Signal<TArgs>::Block()
	{
		d_blocked = true;
	}

	template <typename TArgs>
	void Signal<TArgs>::Unblock()
	{
		d_blocked = false;
	}

	template <typename TArgs>
	bool Signal<TArgs>::IsBlocked() const
	{
		return d_blocked;
	}

	// Sorting
	template <typename TArgs>
	void Signal<TArgs>::Sort(CallbackVec &vec)
	{
		std::sort(vec.begin(), vec.end(), std::greater<Cloneable<CallbackBase<TArgs> > >());
	}

	// Copying
	template <typename TArgs>
	void Signal<TArgs>::Copy(Signal<TArgs> const &other)
	{
		d_blocked = other.d_blocked;
		d_defaultHandler = other.d_defaultHandler;
	}

	template <typename TArgs>
	inline size_t Signal<TArgs>::Size() const
	{
		return d_callbacks.size() + d_callbacksAfter.size();
	}
}
}
}

#endif /* __JESSEVDK_BASE_SIGNALS_SIGNAL_H__ */
