#include "module.ih"

#if defined OSX
string const Module::suffix = ".dylib";
#elif defined WIN32
string const Module::suffix = ".dll";
#else
string const Module::suffix = ".so";
#endif
