#include "filesystem.ih"

string FileSystem::workingDirectory() 
{
	return get_current_dir_name();
}
