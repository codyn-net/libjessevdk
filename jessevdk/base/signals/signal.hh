/*
 *	Signal template class for storing callbacks for a specific callback
 *  signature
 *
 *	Author: Jesse van den Kieboom
 */
#ifndef __JESSEVDK_BASE_SIGNALS_SIGNAL_H__
#define __JESSEVDK_BASE_SIGNALS_SIGNAL_H__

#include <set>
#include <algorithm>
#include <functional>

#include <jessevdk/base/cloneable.hh>
#include <jessevdk/base/signals/callbackbase.hh>
#include <jessevdk/base/signals/callback.hh>
#include <jessevdk/base/signals/create.hh>

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
		typedef std::greater<CallbackBase<TArgs> > Comparator;

		typedef std::multiset<Cloneable<CallbackBase<TArgs> >, Comparator> CallbackVec;
		typedef typename CallbackVec::const_iterator ConstIterator;
		typedef typename CallbackVec::iterator Iterator;

		CallbackVec d_callbacks;
		CallbackVec d_callbacksAfter;

		bool d_blocked;
		Cloneable<CallbackBase<TArgs> > d_defaultHandler;

		public:
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
			template <typename TObject, typename TReturnType, typename TOtherObject, typename TOtherArgs>
			void Add(TObject &obj, TReturnType (TOtherObject::* const function)(TOtherArgs args), int priority = 0);

			template <typename TObject, typename TReturnType, typename TOtherObject>
			void Add(TObject &obj, TReturnType (TOtherObject::* const function)(), int priority = 0);

			/** Register callback.
			  * This functions registers a new callback on the signal with
			  * the specified user data assigned
			  * @param function the callback function
			  * @param userdata the user data to be provided to the callback
			  * functio on emission
			  * @param priority the callback priority
			  * @author Jesse van den Kieboom
			  */
			template <typename TReturnType, typename TOtherUserData, typename TUserData>
			void AddData(TReturnType (*function)(TOtherUserData), TUserData const &userdata, int priority = 0);

			template <typename TReturnType, typename TOtherArgs, typename TOtherUserData, typename TUserData>
			void AddData(TReturnType (*function)(TOtherArgs, TOtherUserData), TUserData const &userdata, int priority = 0);

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
			template <typename TObject, typename TReturnType, typename TOtherObject, typename TOtherUserData, typename TUserData>
			void AddData(TObject &obj, TReturnType (TOtherObject::* const function)(TOtherUserData), TUserData const &userdata, int priority = 0);

			template <typename TObject, typename TReturnType, typename TOtherObject, typename TOtherArgs, typename TOtherUserData, typename TUserData>
			void AddData(TObject &obj, TReturnType (TOtherObject::* const function)(TOtherArgs, TOtherUserData), TUserData const &userdata, int priority = 0);

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
			template <typename TObject, typename TReturnType, typename TOtherObject, typename TOtherArgs>
			void AddAfter(TObject &obj, TReturnType (TOtherObject::* const function)(TOtherArgs args), int priority = 0);

			template <typename TObject, typename TReturnType, typename TOtherObject>
			void AddAfter(TObject &obj, TReturnType (TOtherObject::* const function)(), int priority = 0);

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
			template <typename TReturnType, typename TOtherUserData, typename TUserData>
			void AddAfterData(TReturnType (*function)(TOtherUserData), TUserData const &userdata, int priority = 0);

			template <typename TReturnType, typename TOtherArgs, typename TOtherUserData, typename TUserData>
			void AddAfterData(TReturnType (*function)(TOtherArgs, TOtherUserData), TUserData const &userdata, int priority = 0);

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
			template <typename TObject, typename TReturnType, typename TOtherObject, typename TOtherUserData, typename TUserData>
			void AddAfterData(TObject &obj, TReturnType (TOtherObject::* const function)(TOtherUserData), TUserData const &userdata, int priority = 0);

			template <typename TObject, typename TReturnType, typename TOtherObject, typename TOtherArgs, typename TOtherUserData, typename TUserData>
			void AddAfterData(TObject &obj, TReturnType (TOtherObject::* const function)(TOtherArgs, TOtherUserData), TUserData const &userdata, int priority = 0);

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

			CallbackBase<TArgs> &SetPriority(CallbackBase<TArgs> &callback, int priority);
	};

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
		d_defaultHandler(Create<TArgs>::Callback(function))
	{
	}

	template <typename TArgs>
	template <typename TFunction, typename TObject>
	Signal<TArgs>::Signal(TObject &obj, TFunction function)
	:
		d_blocked(false),
		d_defaultHandler(Create<TArgs>::Callback(obj, function))
	{
	}

	// Adding callbacks
	template <typename TArgs>
	template <typename TFunction>
	void Signal<TArgs>::Add(TFunction function, int priority)
	{
		*this += SetPriority(Create<TArgs>::Callback(function), priority);
	}

	template <typename TArgs>
	template <typename TObject, typename TReturnType, typename TOtherObject, typename TOtherArgs>
	void Signal<TArgs>::Add(TObject &obj, TReturnType (TOtherObject::* const function)(TOtherArgs), int priority)
	{
		*this += SetPriority(Create<TArgs>::Callback(dynamic_cast<TOtherObject &>(obj), function), priority);
	}

	template <typename TArgs>
	template <typename TObject, typename TReturnType, typename TOtherObject>
	void Signal<TArgs>::Add(TObject &obj, TReturnType (TOtherObject::* const function)(), int priority)
	{
		*this += SetPriority(Create<TArgs>::Callback(dynamic_cast<TOtherObject &>(obj), function), priority);
	}

	template <typename TArgs>
	template <typename TReturnType, typename TOtherUserData, typename TUserData>
	void Signal<TArgs>::AddData(TReturnType (*function)(TOtherUserData), TUserData const &userdata, int priority)
	{
		*this += SetPriority(Create<TArgs>::Callback(function, userdata), priority);
	}

	template <typename TArgs>
	template <typename TReturnType, typename TOtherArgs, typename TOtherUserData, typename TUserData>
	void Signal<TArgs>::AddData(TReturnType (*function)(TOtherArgs, TOtherUserData), TUserData const &userdata, int priority)
	{
		*this += SetPriority(Create<TArgs>::Callback(function, userdata), priority);
	}

	template <typename TArgs>
	template <typename TObject, typename TReturnType, typename TOtherObject, typename TOtherUserData, typename TUserData>
	void Signal<TArgs>::AddData(TObject &obj, TReturnType (TOtherObject::* const function)(TOtherUserData), TUserData const &userdata, int priority)
	{
		*this += SetPriority(Create<TArgs>::Callback(obj, function, userdata), priority);
	}

	template <typename TArgs>
	template <typename TObject, typename TReturnType, typename TOtherObject, typename TOtherArgs, typename TOtherUserData, typename TUserData>
	void Signal<TArgs>::AddData(TObject &obj, TReturnType (TOtherObject::* const function)(TOtherArgs, TOtherUserData), TUserData const &userdata, int priority)
	{
		*this += SetPriority(Create<TArgs>::Callback(obj, function, userdata), priority);
	}

	template <typename TArgs>
	template <typename TFunction>
	void Signal<TArgs>::AddAfter(TFunction function, int priority)
	{
		d_callbacksAfter.insert(SetPriority(Create<TArgs>::Callback(function), priority));
	}

	template <typename TArgs>
	template <typename TObject, typename TReturnType, typename TOtherObject>
	void Signal<TArgs>::AddAfter(TObject &obj, TReturnType (TOtherObject::* const function)(), int priority)
	{
		d_callbacksAfter.insert(SetPriority(Create<TArgs>::Callback(obj, function), priority));
	}

	template <typename TArgs>
	template <typename TObject, typename TReturnType, typename TOtherObject, typename TOtherArgs>
	void Signal<TArgs>::AddAfter(TObject &obj, TReturnType (TOtherObject::* const function)(TOtherArgs args), int priority)
	{
		d_callbacksAfter.insert(SetPriority(Create<TArgs>::Callback(obj, function), priority));
	}

	template <typename TArgs>
	template <typename TReturnType, typename TOtherUserData, typename TUserData>
	void Signal<TArgs>::AddAfterData(TReturnType (*function)(TOtherUserData), TUserData const &userdata, int priority)
	{
		d_callbacksAfter.insert(SetPriority(Create<TArgs>::Callback(function, userdata), priority));
	}

	template <typename TArgs>
	template <typename TReturnType, typename TOtherArgs, typename TOtherUserData, typename TUserData>
	void Signal<TArgs>::AddAfterData(TReturnType (*function)(TOtherArgs, TOtherUserData), TUserData const &userdata, int priority)
	{
		d_callbacksAfter.insert(SetPriority(Create<TArgs>::Callback(function, userdata), priority));
	}

	template <typename TArgs>
	template <typename TObject, typename TReturnType, typename TOtherObject, typename TOtherUserData, typename TUserData>
	void Signal<TArgs>::AddAfterData(TObject &obj, TReturnType (TOtherObject::* const function)(TOtherUserData), TUserData const &userdata, int priority)
	{
		d_callbacksAfter.insert(SetPriority(Create<TArgs>::Callback(obj, function, userdata), priority));
	}

	template <typename TArgs>
	template <typename TObject, typename TReturnType, typename TOtherObject, typename TOtherArgs, typename TOtherUserData, typename TUserData>
	void Signal<TArgs>::AddAfterData(TObject &obj, TReturnType (TOtherObject::* const function)(TOtherArgs args, TOtherUserData), TUserData const &userdata, int priority)
	{
		d_callbacksAfter.insert(SetPriority(Create<TArgs>::Callback(obj, function, userdata), priority));
	}

	template <typename TArgs>
	Signal<TArgs> &Signal<TArgs>::operator+=(Cloneable<CallbackBase<TArgs> > const &callback)
	{
		d_callbacks.insert(callback);
		return *this;
	}

	// Removing callbacks
	template <typename TArgs>
	template <typename TFunction>
	void Signal<TArgs>::Remove(TFunction function)
	{
		*this -= Create<TArgs>::Callback(function);
	}

	template <typename TArgs>
	template <typename TFunction, typename TObject>
	void Signal<TArgs>::Remove(TObject &obj, TFunction function)
	{
		*this -= Create<TArgs>::Callback(obj, function);
	}

	template <typename TArgs>
	template <typename TFunction, typename TUserData>
	void Signal<TArgs>::RemoveData(TFunction function, TUserData const &userdata)
	{
		*this -= Create<TArgs>::Callback(function, userdata);
	}

	template <typename TArgs>
	template <typename TFunction, typename TObject, typename TUserData>
	void Signal<TArgs>::RemoveData(TObject &obj, TFunction function, TUserData const &userdata)
	{
		*this -= Create<TArgs>::Callback(obj, function, userdata);
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

				return true;
			}
		}

		return false;
	}

	// Emission
	template <typename TArgs>
	bool Signal<TArgs>::Emit(CallbackVec vec, TArgs &args) const
	{
		if (d_blocked)
		{
			return true;
		}

		for (ConstIterator iter = vec.begin(); iter != vec.end(); iter++)
		{
			if ((*iter)->Emit(args))
			{
				return true;
			}
		}

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

	template <typename TArgs>
	CallbackBase<TArgs> &Signal<TArgs>::SetPriority(CallbackBase<TArgs> &callback, int priority)
	{
		callback.SetPriority(priority);
		return callback;
	}
}
}
}

#endif /* __JESSEVDK_BASE_SIGNALS_SIGNAL_H__ */
