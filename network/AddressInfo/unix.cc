#include "addressinfo.ih"

AddressInfo AddressInfo::Unix(string const &filename) 
{
	if (!FileSystem::directoryExists(FileSystem::dirname(filename)))
	{
		return AddressInfo(-1, 0);
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
	info->ai_addr = (sockaddr *)addr;
	info->ai_next = 0;

	return AddressInfo(0, info);
}
