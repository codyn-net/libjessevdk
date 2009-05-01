#ifndef __BASE_PROPERTYCB_H__
#define __BASE_PROPERTYCB_H__

#include "Signals/Signal/signal.hh"
#include "property.hh"

namespace base
{
	template <template <typename> class TParent, typename Type, typename TObject, typename TReturn>
	class PropertyCb : public TParent<Type>
	{
		typedef TReturn (TObject::*Function)(Type const &);
		
		TObject &d_object;
		Function d_function;

		public:
			PropertyCb(std::string const &name, Type &storage, TObject &object, Function function);
			
			virtual PropertyCb<TParent, Type, TObject, TReturn> *clone() const;
			virtual operator Type const &() const;
			virtual PropertyCb<TParent, Type, TObject, TReturn> &operator=(Type const &value);
		protected:
			virtual void set(Type const &value);
	};
	
	template <template <typename> class TParent, typename Type, typename TObject, typename TReturn>
	PropertyCb<TParent, Type, TObject, TReturn>::PropertyCb(std::string const &name, Type &storage, TObject &object, Function function)
	:
		TParent<Type>(name, storage),
		d_object(object),
		d_function(function)
	{
	}
	
	template <template <typename> class TParent, typename Type, typename TObject, typename TReturn>
	inline void PropertyCb<TParent, Type, TObject, TReturn>::set(Type const &value)
	{
		(d_object.*d_function)(value);
		
		Property<Type>::emitChanged();
	}
	
	template <template <typename> class TParent, typename Type, typename TObject, typename TReturn>
	inline PropertyCb<TParent, Type, TObject, TReturn> &PropertyCb<TParent, Type, TObject, TReturn>::operator=(Type const &value)
	{
		set(value);
		return *this;
	}
	
	template <template <typename> class TParent, typename Type, typename TObject, typename TReturn>
	inline PropertyCb<TParent, Type, TObject, TReturn> *PropertyCb<TParent, Type, TObject, TReturn>::clone() const
	{
		return new PropertyCb<TParent, Type, TObject, TReturn>(*this);
	}
	
	template <template <typename> class TParent, typename Type, typename TObject, typename TReturn>
	inline PropertyCb<TParent, Type, TObject, TReturn>::operator Type const &() const
	{
		return Property<Type>::operator Type const &();
	}
}

#endif /* __BASE_PROPERTYCB_H__ */
