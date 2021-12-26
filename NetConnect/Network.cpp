#include "Network.h"
#include <iostream>


bool NetConnect::Network::initialize()
{
	WSADATA wsadata;
	int wsaResult = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if (wsaResult != 0) {
		std::cerr << "Failed Winsock2 Initialization" << std::endl;
		return false;
	}
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wVersion) != 2) {
		std::cerr << "Failed to Initialize the correct version of Winsock2" << std::endl;
		return false;
	}
	return true;
}
void NetConnect::Network::shutdown()
{
	WSACleanup();
}