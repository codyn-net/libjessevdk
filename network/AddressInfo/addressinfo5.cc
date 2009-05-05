#include "addressinfo.ih"

AddressInfo::AddressInfo(string const &filename) 
{
	if (!FileSystem::directoryExists(FileSystem::dirname(filename)))
	{
		initialize(-1, 0);
		return;
	}
	
	struct sockaddr_un *addr = new sockaddr_un();
	
	addr->sun_family = AF_UNIX;
	strncpy(addr->sun_path, filename.c_str(), 107);
	addr->sun_path[107] = '\0';
	
	struct addrinfo *info = new addrinfo();
	
	info->ai_flags = 0;
	info->ai_family = AF_UNIX;
	info->ai_socktype = SOCK_STREAM;
	info->ai_protocol = 0;
	info->ai_addrlen = sizeof(struct sockaddr_un);
	info->ai_addr = reinterpret_cast<struct sockaddr *>(addr);
	info->ai_next = 0;

	initialize(0, info);
}
