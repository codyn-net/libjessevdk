#ifndef __JESSEVDK_OS_FILE_SYSTEM_H__
#define __JESSEVDK_OS_FILE_SYSTEM_H__

#include <string>

namespace jessevdk
{
namespace os
{
	class FileSystem
	{
		public:
			template <typename Container>
			static bool Find(Container const &container, std::string const &filename, std::string &path);
			static bool Exists(std::string const &filename);
			static bool FileExists(std::string const &filename);
			static bool DirectoryExists(std::string const &filename);

			static bool Realpath(std::string const &path, std::string &real);
			static bool TemporaryFile(std::string &path, std::ofstream &ofstr);

			static bool Move(std::string const &from, std::string const &to);
			static bool Copy(std::string const &from, std::string const &to);

			static std::string Basename(std::string const &filename);
			static std::string Dirname(std::string const &filename);

			static bool ResolveBinary(std::string const &filename, std::string &path);

			static std::string UniqueName(std::string const &filename);

			static bool IsAbsolute(std::string const &path);
			static std::string WorkingDirectory();

			static bool Mkdirs(std::string const &path);

			static bool Remove(std::string const &path, bool recursive = false);
		private:
			/* Private functions */
			FileSystem(); // NI
	};

	template <typename Container>
	bool FileSystem::Find(Container const &container, std::string const &filename, std::string &path)
	{
		for (typename Container::const_iterator iter = container.begin(); iter != container.end(); ++iter)
		{
			/* Construct path */
			std::string real;

			if (*iter != "")
			{
				if (!Realpath(*iter, real))
				{
					continue;
				}

				path = real + "/" + filename;
			}
			else
			{
				path = filename;
			}

			if (FileExists(path))
			{
				return true;
			}
		}

		return false;
	}
}
}

#endif /* __JESSEVDK_OS_FILE_SYSTEM_H__ */
