#ifndef __BASE_PROPERTY2_H__
#define __BASE_PROPERTY2_H__

#include "propertycommon.hh"

namespace base
{
	template <>
	class Property<std::string> : public PropertyCommon<std::string>
	{
		public:
			Property<std::string>(std::string const &name, std::string &storage);
			
			virtual Property<std::string> *clone() const;
			virtual Property<std::string> &operator=(std::string const &value);

			virtual void set(std::string const &value);
			virtual bool serializable() const;
		
			void emitChanged();
			signals::Signal<Property<std::string> const> onChanged;
			
			virtual operator std::string() const;
	};
	
	inline Property<std::string>::Property(std::string const &name, std::string &storage)
	:
		PropertyCommon<std::string>(name, storage)
	{
	}
	
	inline Property<std::string> *Property<std::string>::clone() const
	{
		return new Property<std::string>(*this);
	}
	
	inline void Property<std::string>::emitChanged()
	{
		onChanged(*this);
	}
	
	inline void Property<std::string>::set(std::string const &value)
	{
		PropertyCommon<std::string>::set(value);
		emitChanged();
	}
	
	inline bool Property<std::string>::serializable() const
	{
		return true;
	}
	
	inline Property<std::string> &Property<std::string>::operator=(std::string const &value)
	{
		set(value);
		return *this;
	}
	
	inline Property<std::string>::operator std::string() const
	{
		return std::string(*this);
	}
}

#endif /* __BASE_PROPERTY2_H__ */
