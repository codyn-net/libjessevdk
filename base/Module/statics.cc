#include "module.ih"

#if defined OSX
string const Module::suffix = ".dylib";
string const Module::prefix = "lib";
#elif defined WIN32
string const Module::suffix = ".dll";
string const Module::prefix = "";
#else
string const Module::suffix = ".so";
string const Module::prefix = "lib";
#endif
