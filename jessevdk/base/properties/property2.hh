#ifndef __JESSEVDK_BASE_PROPERTIES_PROPERTY2_H__
#define __JESSEVDK_BASE_PROPERTIES_PROPERTY2_H__

#include <jessevdk/base/properties/propertycommon.hh>

namespace jessevdk
{
namespace base
{
namespace properties
{
	template <>
	class Property<std::string> : public PropertyCommon<std::string>
	{
		public:
			Property<std::string>(std::string const &name, std::string &storage);

			virtual Property<std::string> *Clone() const;
			virtual Property<std::string> &operator=(std::string const &value);

			virtual void Set(std::string const &value);
			virtual bool Serializable() const;

			void EmitChanged();
			signals::Signal<Property<std::string> const> OnChanged;

			virtual operator std::string() const;
	};

	inline Property<std::string>::Property(std::string const &name, std::string &storage)
	:
		PropertyCommon<std::string>(name, storage)
	{
	}

	inline Property<std::string> *
	Property<std::string>::Clone() const
	{
		return new Property<std::string>(*this);
	}

	inline void
	Property<std::string>::EmitChanged()
	{
		OnChanged(*this);
	}

	inline void
	Property<std::string>::Set(std::string const &value)
	{
		PropertyCommon<std::string>::Set(value);
		EmitChanged();
	}

	inline bool
	Property<std::string>::Serializable() const
	{
		return true;
	}

	inline Property<std::string> &
	Property<std::string>::operator=(std::string const &value)
	{
		Set(value);
		return *this;
	}

	inline Property<std::string>::operator std::string() const
	{
		return std::string(*this);
	}
}
}
}

#endif /* __JESSEVDK_BASE_PROPERTIES_PROPERTY2_H__ */
