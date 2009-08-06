%module(package="jessevdk") base

%include base.i

%{
#include <base/Properties/properties.hh>
%}

namespace base
{
	class Properties : public base::Augmentation
	{
		public:
			Properties(Object &object);

			/* Public functions */
			template <typename Type>
			Property<Type> &property(std::string const &name);
		
			template <typename Type>
			Property<Type> const &property(std::string const &name) const;
		
			base::PropertyBase const &property(std::string const &name) const;
			base::PropertyBase &property(std::string const &name);
		
			std::vector<std::string> properties() const;
		
			template <typename Type>
			void setProperty(std::string const &name, Type const &value);
			virtual bool hasProperty(std::string const &name);

			template <typename Type>
			Property<Type> &addProperty(std::string const &name, Property<Type> const &property);
		
			template <typename Type>
			Property<Type> &registerProperty(std::string const &name, Type &storage);
		
			template <typename Type, typename TObject, typename TFuncObject, typename TReturn>
			Property<Type> &registerProperty(std::string const &name, Type &storage, TObject &object, TReturn (TFuncObject::*function)(Type const &));
		
			template <typename Type, typename TObject, typename TReturn>
			Property<Type> &registerProperty(std::string const &name, Type &storage, TReturn (TObject::*function)(Type const &));
	};
}

%inline
{
	using namespace base;
}
