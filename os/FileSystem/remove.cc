#include "filesystem.ih"

bool FileSystem::remove(string const &path, bool recursive)
{
	if (fileExists(path))
	{
		return ::unlink(path.c_str()) == 0;
	}
	else if (directoryExists(path))
	{
		if (recursive)
		{
			DIR *d = opendir(path.c_str());
			
			if (d)
			{
				struct dirent *dent;
	
				while ((dent = readdir(d)))
				{
					if (string(dent->d_name) == "." || string(dent->d_name) == "..")
					{
						continue;
					}
						
					string s = Glib::build_filename(path, dent->d_name);
					
					if (!remove(s, true))
					{
						return false;
					}
				}

				closedir(d);
			}
		}
		
		return ::rmdir(path.c_str()) == 0;
	}
	else
	{
		return false;
	}
}
