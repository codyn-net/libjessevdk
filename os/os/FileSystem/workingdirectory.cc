#include "filesystem.ih"

string FileSystem::workingDirectory() 
{
	return Glib::get_current_dir();
}
