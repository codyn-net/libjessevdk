#include "filesystem.ih"

bool FileSystem::temporaryFile(string &path, ofstream &ofstr) 
{
	char p[] = "/tmp/optimization.XXXXXX";
	int f = mkstemp(p);
	
	if (f == -1)
		return false;
	
	path = p;
	ofstr.open(p, ios::out | ios::trunc);
	
	return ofstr;
}
