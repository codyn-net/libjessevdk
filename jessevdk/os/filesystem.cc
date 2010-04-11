#include "filesystem.hh"

#include <cstring>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cerrno>
#include <vector>
#include <sstream>
#include <dirent.h>

#include <jessevdk/base/string.hh>
#include <glibmm.h>
#include <jessevdk/os/environment.hh>

#include <libgen.h>

using namespace std;
using namespace jessevdk::os;
using namespace jessevdk::base;

string
FileSystem::Basename(string const &filename)
{
	char *buf = new char[filename.size() + 1];
	strcpy(buf, filename.c_str());

	char *copy = ::basename(buf);
	string result(copy);

	free(buf);
	return result;
}

bool
FileSystem::Copy(string const &from, string const &to)
{
	if (!Exists(from))
	{
		return false;
	}

	ifstream ifstr(from.c_str(), ios::in);
	ofstream ofstr(to.c_str(), ios::trunc | ios::out);

	return ofstr << ifstr.rdbuf();
}

bool
FileSystem::DirectoryExists(string const &filename)
{
	struct stat buf;
	return (stat(filename.c_str(), &buf) == 0) && S_ISDIR(buf.st_mode);
}

string
FileSystem::Dirname(string const &filename)
{
	char *buf = new char[filename.size() + 1];
	strcpy(buf, filename.c_str());

	char *copy = ::dirname(buf);
	string result(copy);

	delete[] buf;
	return result;
}

bool
FileSystem::Exists(string const &filename)
{
	return FileExists(filename) || DirectoryExists(filename);
}

bool
FileSystem::FileExists(string const &filename)
{
	struct stat buf;
	return (stat(filename.c_str(), &buf) == 0) &&
	       (S_ISREG(buf.st_mode) || S_ISLNK(buf.st_mode));
}

bool
FileSystem::IsAbsolute(string const &path)
{
	return !path.empty() && path[0] == '/';
}

bool
FileSystem::Mkdirs(string const &path)
{
	vector<string> parts = String(path).Split("/");
	string full;

	for (vector<string>::iterator iter = parts.begin(); iter != parts.end(); ++iter)
	{
		full = full + "/" + *iter;

		if (!DirectoryExists(full))
		{
			if (::mkdir(full.c_str(), 0755) != 0)
			{
				return false;
			}
		}
	}

	return true;
}

bool
FileSystem::Move(string const &from, string const &to)
{
	if (!Copy(from, to))
	{
		return false;
	}

	// Remove `from`
	unlink(from.c_str());
	return true;
}

bool
FileSystem::Realpath(string const &path, string &real)
{
	char p[PATH_MAX];

	char *ptr = ::realpath(path.c_str(), p);

	if (!ptr)
	{
		return false;
	}

	real = ptr;
	return true;
}

bool
FileSystem::Remove(string const &path, bool recursive)
{
	if (FileExists(path))
	{
		return ::unlink(path.c_str()) == 0;
	}
	else if (DirectoryExists(path))
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

					if (!Remove(s, true))
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

bool
FileSystem::ResolveBinary(string const &filename, string &path)
{
	vector<string> paths = Environment::Path("PATH");
	return FileSystem::Find(paths, filename, path);
}

bool
FileSystem::TemporaryFile(string &path, ofstream &ofstr)
{
	char p[] = "/tmp/optimization.XXXXXX";
	int f = mkstemp(p);

	if (f == -1)
	{
		return false;
	}

	path = p;
	ofstr.open(p, ios::out | ios::trunc);

	return ofstr;
}

string
FileSystem::UniqueName(string const &filename)
{
	string path;

	if (!Realpath(filename, path))
	{
		return filename;
	}

	size_t i = 1;
	string original = path;

	while (FileExists(path))
	{
		stringstream s;
		s << original << "." << i++;

		path = s.str();
	}

	return path;
}

string
FileSystem::WorkingDirectory()
{
	return Glib::get_current_dir();
}
