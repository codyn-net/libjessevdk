#ifndef __JESSEVDK_BASE_PROPERTIES_PROPERTY1_H__
#define __JESSEVDK_BASE_PROPERTIES_PROPERTY1_H__

#include <jessevdk/base/properties/propertycommon.hh>
#include <sstream>
#include <iosfwd>

namespace jessevdk
{
namespace base
{
namespace properties
{
	template <typename Type>
	class Property : public PropertyCommon<Type>
	{
		public:
			Property(std::string const &name, Type &storage);

			virtual Property<Type> *Clone() const;
			virtual Property<Type> &operator=(Type const &value);
			virtual Property<Type> &operator=(std::string const &value);
			virtual void Set(Type const &value);

			void EmitChanged();
			signals::Signal<Property<Type> const> OnChanged;
	};

	template <typename Type>
	inline Property<Type>::Property(std::string const &name, Type &storage)
	:
		PropertyCommon<Type>(name, storage)
	{
	}

	template <typename Type>
	inline Property<Type> *
	Property<Type>::Clone() const
	{
		return new Property<Type>(*this);
	}

	template <typename Type>
	inline void
	Property<Type>::EmitChanged()
	{
		OnChanged(*this);
	}

	template <typename Type>
	inline void
	Property<Type>::Set(Type const &value)
	{
		PropertyCommon<Type>::Set(value);
		EmitChanged();
	}

	template <typename Type>
	inline Property<Type> &
	Property<Type>::operator=(Type const &value)
	{
		Set(value);
		return *this;
	}

	template <typename Type>
	inline Property<Type> &
	Property<Type>::operator=(std::string const &value)
	{
		return *this;
	}
}
}
}

#endif /* __JESSEVDK_BASE_PROPERTIES_PROPERTY1_H__ */
