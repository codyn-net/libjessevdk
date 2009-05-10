#ifndef __BASE_PROPERTY1_H__
#define __BASE_PROPERTY1_H__

#include <base/Properties/Property/propertycommon.hh>
#include <sstream>
#include <iosfwd>

namespace base
{
	template <typename Type>
	class Property : public PropertyCommon<Type>
	{
		public:
			Property(std::string const &name, Type &storage);
			
			virtual Property<Type> *clone() const;
			virtual Property<Type> &operator=(Type const &value);
			virtual Property<Type> &operator=(std::string const &value);
			virtual void set(Type const &value);
		
			void emitChanged();
			signals::Signal<Property<Type> const> onChanged;
	};
	
	template <typename Type>
	inline Property<Type>::Property(std::string const &name, Type &storage)
	:
		PropertyCommon<Type>(name, storage)
	{
	}
	
	template <typename Type>
	inline Property<Type> *Property<Type>::clone() const
	{
		return new Property<Type>(*this);
	}
	
	template <typename Type>
	inline void Property<Type>::emitChanged()
	{
		onChanged(*this);
	}
	
	template <typename Type>
	inline void Property<Type>::set(Type const &value)
	{
		PropertyCommon<Type>::set(value);
		emitChanged();
	}
	
	template <typename Type>
	inline Property<Type> &Property<Type>::operator=(Type const &value)
	{
		set(value);
		return *this;
	}
	
	template <typename Type>
	inline Property<Type> &Property<Type>::operator=(std::string const &value)
	{
		return *this;
	}
}

#endif /* __BASE_PROPERTY1_H__ */
