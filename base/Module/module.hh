#ifndef __BASE_MODULE_H__
#define __BASE_MODULE_H__

#include <string>

namespace base
{
	class Module
	{
		std::string d_path;
		void *d_handle;

		bool d_state;
		std::string d_error;
		
		public:
			static std::string const suffix;

			/* Constructor/destructor */
			Module(std::string const &path);
			~Module();

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
	
	template <typename TFunction>
	TFunction Module::lookup(std::string const &symbol)
	{
		if (!d_handle)
			return Type(0);
		
		void *s = dlsym(d_handle, symbol.c_str());
		
		if (!s)
		{
			d_error = dlerror();
			return 0;
		}
		
		return reinterpret_cast<TFunction>(s);
	}
	
}

#endif /* __BASE_MODULE_H__ */
