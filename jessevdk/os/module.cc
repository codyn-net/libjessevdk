#include "module.hh"

#include <jessevdk/os/filesystem.hh>
#include <jessevdk/base/string.hh>

using namespace std;
using namespace jessevdk::base;
using namespace jessevdk::os;

#if defined PLATFORM_OSX
string const Module::suffix = ".dylib";
string const Module::prefix = "lib";
#elif defined WIN32
string const Module::suffix = ".dll";
string const Module::prefix = "";
#else
string const Module::suffix = ".so";
string const Module::prefix = "lib";
#endif

Module::Data::~Data()
{
	if (state && handle)
	{
		dlclose(handle);
	}
}

Module::Module(string const &path)
{
	d_data = new Data();
	AddPrivateData(d_data);

	d_data->path = ResolvePath(path);
	d_data->state = Open();
}

Module::Module()
{
	d_data = new Data();
	AddPrivateData(d_data);

	d_data->state = false;
	d_data->handle = 0;
}

bool
Module::Open()
{
	if (d_data->path == "")
	{
		d_data->error = "File does not exist";
		return false;
	}

	d_data->handle = dlopen(d_data->path.c_str(), RTLD_LAZY | RTLD_GLOBAL);

	if (!d_data->handle)
	{
		d_data->error = dlerror();
		return false;
	}

	return true;
}

string
Module::ResolvePath(string const &path) const
{
	String s(path);

	if (!s.EndsWith(Module::suffix))
	{
		s += Module::suffix;
	}

	string res;
	return FileSystem::Realpath(path, res) ? res : "";
}
