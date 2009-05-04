#ifndef __OS_FILE_SYSTEM_H__
#define __OS_FILE_SYSTEM_H__

#include <string>

namespace os
{
	class FileSystem
	{
		public:
			template <typename Container>
			static bool find(Container const &container, std::string const &filename, std::string &path);
			static bool exists(std::string const &filename);
			static bool fileExists(std::string const &filename);
			static bool directoryExists(std::string const &filename);
				
			static bool realpath(std::string const &path, std::string &real);
			static bool temporaryFile(std::string &path, std::ofstream &ofstr);
		
			static bool move(std::string const &from, std::string const &to);
			static bool copy(std::string const &from, std::string const &to);
		
			static std::string basename(std::string const &filename);
			static std::string dirname(std::string const &filename);
			
			static bool resolveBinary(std::string const &filename, std::string &path);
		private:
			/* Private functions */
			FileSystem(); // NI
	};

	template <typename Container>
	bool FileSystem::find(Container const &container, std::string const &filename, std::string &path)
	{
		for (typename Container::const_iterator iter = container.begin(); iter != container.end(); ++iter)
		{
			/* Construct path */
			std::string real;
		
			if (*iter != "")
			{
				if (!realpath(*iter, real))
					continue;

				path = real + "/" + filename;
			}
			else
				path = filename;
		
			if (fileExists(path))
				return true;
		}
	
		return false;
	}
}

#endif /* __OS_FILE_SYSTEM_H__ */
