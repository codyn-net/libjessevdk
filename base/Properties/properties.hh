#ifndef __BASE_PROPERTIES_H__
#define __BASE_PROPERTIES_H__

#include <map>
#include <exception>
#include <vector>

#include <base/Cloneable/cloneable.hh>
#include <base/Object/object.hh>
#include <base/Properties/Property/property.hh>

namespace base
{
	class Properties : public Object::Augmentation
	{
		struct Data : public Object::PrivateData
		{
			std::map<std::string, Cloneable<PropertyBase> > properties;
		};
		
		public:
			class read_only : public std::exception
			{
				std::string d_message;
				
				public:
					read_only(std::string const &name)
					{
						d_message = std::string("cannot write read-only property `") + name + "`";
					}
					
					~read_only() throw() {};
					virtual char const *what() const throw() { return d_message.c_str(); };
			};
				
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
			Property<Type> &property(std::string const &name);
			
			template <typename Type>
			Property<Type> const &property(std::string const &name) const;
			
			PropertyBase const &property(std::string const &name) const;
			PropertyBase &property(std::string const &name);
			
			std::vector<std::string> properties() const;
			
			template <typename Type>
			void setProperty(std::string const &name, Type const &value);
			virtual bool hasProperty(std::string const &name);

			template <typename Type>
			Property<Type> &addProperty(std::string const &name, Property<Type> const &property);
			
			template <bool canSerialize, typename Type>
			Property<Type> &registerProperty(std::string const &name, Type &storage);
			
			template <typename Type>
			Property<Type> &registerProperty(std::string const &name, Type &storage);
			
			template <bool canSerialize, typename Type, typename TObject, typename TFuncObject, typename TReturn>
			Property<Type> &registerProperty(std::string const &name, Type &storage, TObject &object, TReturn (TFuncObject::*function)(Type const &));
			
			template <typename Type, typename TObject, typename TFuncObject, typename TReturn>
			Property<Type> &registerProperty(std::string const &name, Type &storage, TObject &object, TReturn (TFuncObject::*function)(Type const &));
			
			template <bool canSerialize, typename Type, typename TObject, typename TReturn>
			Property<Type> &registerProperty(std::string const &name, Type &storage, TReturn (TObject::*function)(Type const &));
			
			template <typename Type, typename TObject, typename TReturn>
			Property<Type> &registerProperty(std::string const &name, Type &storage, TReturn (TObject::*function)(Type const &));

		protected:			
			template <typename Type>
			void readOnly(Property<Type> const &value);
			
			virtual PropertyBase &getProperty(std::string const &name);
		private:
			template <typename Type>
			Property<Type> &registerProperty(std::string const &name, Type &storage, Serializable<true>);

			template <typename Type>
			Property<Type> &registerProperty(std::string const &name, Type &storage, Serializable<false>);
			
			template <typename Type, typename TObject, typename TFuncObject, typename TReturn>
			Property<Type> &registerProperty(std::string const &name, Type &storage, TObject &object, TReturn (TFuncObject::*function)(Type const &), Serializable<true>);
			
			template <typename Type, typename TObject, typename TFuncObject, typename TReturn>
			Property<Type> &registerProperty(std::string const &name, Type &storage, TObject &object, TReturn (TFuncObject::*function)(Type const &), Serializable<false>);
	};
	
	template <typename Type>
	Property<Type> &Properties::property(std::string const &name)
	{
		return dynamic_cast<Property<Type> &>(property(name));
	}
	
	template <typename Type>
	Property<Type> const &Properties::property(std::string const &name) const
	{
		return dynamic_cast<Property<Type> const &>(property(name));
	}
	
	inline PropertyBase &Properties::getProperty(std::string const &name)
	{
		return *(data<Data>()->properties)[name];
	}

	inline PropertyBase const &Properties::property(std::string const &name) const
	{
		return const_cast<Properties *>(this)->getProperty(name);
	}

	inline PropertyBase &Properties::property(std::string const &name)
	{
		return getProperty(name);
	}

	template <typename Type>
	Property<Type> &Properties::addProperty(std::string const &name, Property<Type> const &prop)
	{
		data<Data>()->properties[name] = prop;
		return property<Type>(name);
	}

	template <typename Type>
	Property<Type> &Properties::registerProperty(std::string const &name, Type &storage, Serializable<true>)
	{
		return addProperty(name, PropertySerial<Type>(name, storage));
	}

	template <typename Type>
	Property<Type> &Properties::registerProperty(std::string const &name, Type &storage, Serializable<false>)
	{
		return addProperty(name, Property<Type>(name, storage));
	}

	template <bool canSerialize, typename Type>
	Property<Type> &Properties::registerProperty(std::string const &name, Type &storage)
	{
		return registerProperty(name, storage, Serializable<canSerialize>());
	}

	template <typename Type>
	Property<Type> &Properties::registerProperty(std::string const &name, Type &storage)
	{
		return registerProperty(name, storage, Serializable<true>());
	}

	template <typename Type, typename TObject, typename TFuncObject, typename TReturn>
	Property<Type> &Properties::registerProperty(std::string const &name, Type &storage, TObject &object, TReturn (TFuncObject::*function)(Type const &), Serializable<true>)
	{
		return addProperty(name, PropertyCb<PropertySerial, Type, TFuncObject, TReturn>(name, storage, dynamic_cast<TFuncObject &>(object), function));
	}

	template <typename Type, typename TObject, typename TFuncObject, typename TReturn>
	Property<Type> &Properties::registerProperty(std::string const &name, Type &storage, TObject &object, TReturn (TFuncObject::*function)(Type const &), Serializable<false>)
	{
		return addProperty(name, PropertyCb<Property, Type, TFuncObject, TReturn>(name, storage, dynamic_cast<TFuncObject &>(object), function));
	}

	template <bool canSerialize, typename Type, typename TFuncObject, typename TObject, typename TReturn>
	Property<Type> &Properties::registerProperty(std::string const &name, Type &storage, TFuncObject &object, TReturn (TObject::*function)(Type const &))
	{
		return registerProperty(name, storage, object, function, Serializable<canSerialize>());
	}

	template <typename Type, typename TFuncObject, typename TObject, typename TReturn>
	Property<Type> &Properties::registerProperty(std::string const &name, Type &storage, TFuncObject &object, TReturn (TObject::*function)(Type const &))
	{
		return registerProperty(name, storage, object, function, Serializable<false>());
	}

	template <bool canSerialize, typename Type, typename TObject, typename TReturn>
	Property<Type> &Properties::registerProperty(std::string const &name, Type &storage, TReturn (TObject::*function)(Type const &))
	{
		return registerProperty(name, storage, dynamic_cast<TObject &>(*this), function, Serializable<canSerialize>());
	}

	template <typename Type, typename TObject, typename TReturn>
	Property<Type> &Properties::registerProperty(std::string const &name, Type &storage, TReturn (TObject::*function)(Type const &))
	{
		return registerProperty(name, storage, dynamic_cast<TObject &>(*this), function, Serializable<true>());
	}

	template <typename Type>
	void Properties::setProperty(std::string const &name, Type const &value)
	{
		PropertyBase &prop = property(name);
		
		try
		{
			(dynamic_cast<Property<Type> &>(prop)) = value;
		}
		catch (std::bad_cast &e)
		{
		}
	}

	template <typename Type>
	void Properties::readOnly(Property<Type> const &value)
	{
		throw read_only(value.name());
	}
}

#endif /* __BASE_PROPERTIES_H__ */
