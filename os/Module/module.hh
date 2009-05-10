#ifndef __BASE_MODULE_H__
#define __BASE_MODULE_H__

#include "Object/object.hh"
#include <string>
#include <dlfcn.h>

namespace base
{
	class Module : base::Object
	{
		struct Data : base::Object::PrivateData
		{
			std::string path;
			void *handle;

			bool state;
			std::string error;
			
			~Data();
		};
		
		Data *d_data;
		
		public:
			static std::string const suffix;
			static std::string const prefix;

			/* Constructor/destructor */
			Module();
			Module(std::string const &path);

			/* Public functions */
			operator bool() const;
			std::string const &error() const;
			
			template <typename Type>
			Type lookup(std::string const &symbol);
		private:
			/* Private functions */
			std::string resolvePath(std::string const &path) const;
			bool open();
		
	};
	
	inline Module::operator bool() const
	{
		return d_data->state && d_data->handle;
	}
	
	inline std::string const &Module::error() const
	{
		return d_data->error;
	}
	
	template <typename TFunction>
	TFunction Module::lookup(std::string const &symbol)
	{
		if (!d_data->state || !d_data->handle)
			return TFunction(0);
		
		void *s = ::dlsym(d_data->handle, symbol.c_str());
		
		if (!s)
		{
			d_data->error = dlerror();
			return TFunction(0);
		}
		
		return reinterpret_cast<TFunction>(s);
	}
	
}

#endif /* __BASE_MODULE_H__ */
