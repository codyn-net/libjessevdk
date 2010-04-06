#ifndef __JESSEVDK_OS_MODULE_H__
#define __JESSEVDK_OS_MODULE_H__

#include <jessevdk/base/object.hh>
#include <string>
#include <dlfcn.h>

namespace jessevdk
{
namespace os
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
			static std::string const Suffix;
			static std::string const Prefix;

			/* Constructor/destructor */
			Module();
			Module(std::string const &path);

			/* Public functions */
			operator bool() const;
			std::string const &Error() const;

			template <typename Type>
			Type Lookup(std::string const &symbol);

			static bool IsModuleName(std::string const &name);
		private:
			/* Private functions */
			std::string ResolvePath(std::string const &path) const;
			bool Open();

	};

	inline Module::operator bool() const
	{
		return d_data->state && d_data->handle;
	}

	inline std::string const &Module::Error() const
	{
		return d_data->error;
	}

	template <typename TFunction>
	TFunction Module::Lookup(std::string const &symbol)
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
}

#endif /* __JESSEVDK_OS_MODULE_H__ */
