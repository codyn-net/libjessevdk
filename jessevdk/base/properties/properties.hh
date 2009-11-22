#ifndef __JESSEVDK_BASE_PROPERTIES_H__
#define __JESSEVDK_BASE_PROPERTIES_H__

#include <map>
#include <exception>
#include <vector>

#include <jessevdk/base/cloneable.hh>
#include <jessevdk/base/object.hh>
#include <jessevdk/base/properties/property.hh>
#include <jessevdk/base/exceptions/readonly.hh>

namespace jessevdk
{
namespace base
{
namespace properties
{
	class Properties : public Object::Augmentation
	{
		struct Data : public Object::PrivateData
		{
			std::map<std::string, Cloneable<PropertyBase> > properties;
		};

		public:
			template <int T>
			struct Serializable
			{
				enum Value
				{
					value = T
				};
			};

			Properties(Object &object);

			/* Public functions */
			template <typename Type>
			Property<Type> &GetProperty(std::string const &name);

			template <typename Type>
			Property<Type> const &GetProperty(std::string const &name) const;

			PropertyBase const &GetProperty(std::string const &name) const;
			PropertyBase &GetProperty(std::string const &name);

			std::vector<std::string> Names() const;

			template <typename Type>
			void SetProperty(std::string const &name, Type const &value);
			virtual bool HasProperty(std::string const &name);

			template <typename Type>
			Property<Type> &AddProperty(std::string const &name, Property<Type> const &property);

			template <bool canSerialize, typename Type>
			Property<Type> &Register(std::string const &name, Type &storage);

			template <typename Type>
			Property<Type> &Register(std::string const &name, Type &storage);

			template <bool canSerialize, typename Type, typename TObject, typename TFuncObject, typename TReturn>
			Property<Type> &Register(std::string const &name, Type &storage, TObject &object, TReturn (TFuncObject::*function)(Type const &));

			template <typename Type, typename TObject, typename TFuncObject, typename TReturn>
			Property<Type> &Register(std::string const &name, Type &storage, TObject &object, TReturn (TFuncObject::*function)(Type const &));

			template <bool canSerialize, typename Type, typename TObject, typename TReturn>
			Property<Type> &Register(std::string const &name, Type &storage, TReturn (TObject::*function)(Type const &));

			template <typename Type, typename TObject, typename TReturn>
			Property<Type> &Register(std::string const &name, Type &storage, TReturn (TObject::*function)(Type const &));

		protected:
			template <typename Type>
			void Unreadable(Property<Type> const &value);

			virtual PropertyBase &GetPropertyBase(std::string const &name);
		private:
			template <typename Type>
			Property<Type> &Register(std::string const &name, Type &storage, Serializable<true>);

			template <typename Type>
			Property<Type> &Register(std::string const &name, Type &storage, Serializable<false>);

			template <typename Type, typename TObject, typename TFuncObject, typename TReturn>
			Property<Type> &Register(std::string const &name, Type &storage, TObject &object, TReturn (TFuncObject::*function)(Type const &), Serializable<true>);

			template <typename Type, typename TObject, typename TFuncObject, typename TReturn>
			Property<Type> &Register(std::string const &name, Type &storage, TObject &object, TReturn (TFuncObject::*function)(Type const &), Serializable<false>);
	};

	template <typename Type>
	Property<Type> &Properties::GetProperty(std::string const &name)
	{
		return dynamic_cast<Property<Type> &>(GetProperty(name));
	}

	template <typename Type>
	Property<Type> const &Properties::GetProperty(std::string const &name) const
	{
		return dynamic_cast<Property<Type> const &>(GetProperty(name));
	}

	inline PropertyBase &Properties::GetPropertyBase(std::string const &name)
	{
		return *(Object::Augmentation::Data<Data>()->properties)[name];
	}

	inline PropertyBase const &Properties::GetProperty(std::string const &name) const
	{
		return const_cast<Properties *>(this)->GetPropertyBase(name);
	}

	inline PropertyBase &Properties::GetProperty(std::string const &name)
	{
		return GetPropertyBase(name);
	}

	template <typename Type>
	Property<Type> &Properties::AddProperty(std::string const &name, Property<Type> const &prop)
	{
		Object::Augmentation::Data<Data>()->properties[name] = prop;
		return Property<Type>(name);
	}

	template <typename Type>
	Property<Type> &Properties::Register(std::string const &name, Type &storage, Serializable<true>)
	{
		return AddProperty(name, PropertySerial<Type>(name, storage));
	}

	template <typename Type>
	Property<Type> &Properties::Register(std::string const &name, Type &storage, Serializable<false>)
	{
		return AddProperty(name, Property<Type>(name, storage));
	}

	template <bool canSerialize, typename Type>
	Property<Type> &Properties::Register(std::string const &name, Type &storage)
	{
		return Register(name, storage, Serializable<canSerialize>());
	}

	template <typename Type>
	Property<Type> &Properties::Register(std::string const &name, Type &storage)
	{
		return Register(name, storage, Serializable<true>());
	}

	template <typename Type, typename TObject, typename TFuncObject, typename TReturn>
	Property<Type> &Properties::Register(std::string const &name, Type &storage, TObject &object, TReturn (TFuncObject::*function)(Type const &), Serializable<true>)
	{
		return AddProperty(name, PropertyCb<PropertySerial, Type, TFuncObject, TReturn>(name, storage, dynamic_cast<TFuncObject &>(object), function));
	}

	template <typename Type, typename TObject, typename TFuncObject, typename TReturn>
	Property<Type> &Properties::Register(std::string const &name, Type &storage, TObject &object, TReturn (TFuncObject::*function)(Type const &), Serializable<false>)
	{
		return AddProperty(name, PropertyCb<Property, Type, TFuncObject, TReturn>(name, storage, dynamic_cast<TFuncObject &>(object), function));
	}

	template <bool canSerialize, typename Type, typename TFuncObject, typename TObject, typename TReturn>
	Property<Type> &Properties::Register(std::string const &name, Type &storage, TFuncObject &object, TReturn (TObject::*function)(Type const &))
	{
		return Register(name, storage, object, function, Serializable<canSerialize>());
	}

	template <typename Type, typename TFuncObject, typename TObject, typename TReturn>
	Property<Type> &Properties::Register(std::string const &name, Type &storage, TFuncObject &object, TReturn (TObject::*function)(Type const &))
	{
		return Register(name, storage, object, function, Serializable<false>());
	}

	template <bool canSerialize, typename Type, typename TObject, typename TReturn>
	Property<Type> &Properties::Register(std::string const &name, Type &storage, TReturn (TObject::*function)(Type const &))
	{
		return Register(name, storage, dynamic_cast<TObject &>(*this), function, Serializable<canSerialize>());
	}

	template <typename Type, typename TObject, typename TReturn>
	Property<Type> &Properties::Register(std::string const &name, Type &storage, TReturn (TObject::*function)(Type const &))
	{
		return Register(name, storage, dynamic_cast<TObject &>(*this), function, Serializable<true>());
	}

	template <typename Type>
	void Properties::SetProperty(std::string const &name, Type const &value)
	{
		PropertyBase &prop = GetProperty(name);

		try
		{
			(dynamic_cast<Property<Type> &>(prop)) = value;
		}
		catch (std::bad_cast &e)
		{
		}
	}

	template <typename Type>
	void Properties::Unreadable(Property<Type> const &value)
	{
		throw jessevdk::base::exceptions::ReadOnly(std::string("cannot write read-only property `") + value.Name() + "`");
	}
}
}
}

#endif /* __JESSEVDK_BASE_PROPERTIES_H__ */
