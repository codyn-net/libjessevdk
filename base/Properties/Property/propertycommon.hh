#ifndef __BASE_PROPERTY_COMMON_H__
#define __BASE_PROPERTY_COMMON_H__

#include "Signals/Signal/signal.hh"
#include "propertybase.hh"

#include <ostream>

namespace base
{
	template <typename Type>
	class PropertyCommon : public PropertyBase
	{
		std::string d_name;
		Type &d_storage;
		
		public:
			PropertyCommon(std::string const &name, Type &storage);

			virtual PropertyCommon<Type> *clone() const;
			virtual operator Type const &() const;
			
			bool operator==(PropertyCommon<Type> const &other) const;
			
			std::string const &name() const;
		protected:
			virtual void set(Type const &value);
	};
	
	template <typename Type>
	inline PropertyCommon<Type>::PropertyCommon(std::string const &name, Type &storage)
	:
		d_name(name),
		d_storage(storage)
	{
	}

	template <typename Type>
	inline PropertyCommon<Type> *PropertyCommon<Type>::clone() const
	{
		return new PropertyCommon<Type>(*this);
	}
	
	template <typename Type>
	inline PropertyCommon<Type>::operator Type const &() const
	{
		return d_storage;
	}
	
	template <typename Type>
	inline void PropertyCommon<Type>::set(Type const &value)
	{
		d_storage = value;
	}
	
	template <typename Type>
	inline bool PropertyCommon<Type>::operator==(PropertyCommon<Type> const &other) const
	{
		return operator Type const &() == other.operator Type const &();;
	}
	
	template <typename Type>
	inline std::string const &PropertyCommon<Type>::name() const
	{
		return d_name;
	}

	template <typename Type>
	std::ostream &operator<<(std::ostream &ostr, PropertyCommon<Type> const &property)
	{
		return ostr << (Type const &)property;
	}
}

#endif /* __BASE_PROPERTY_COMMON_H__ */
