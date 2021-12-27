#pragma once
#include "IPVersion.h"
#include <WS2tcpip.h>
#include <string>
#include <vector>

namespace NetConnect {
	class IPEndpoint {
	public:
		IPEndpoint(const char* ip, unsigned short port);
		IPEndpoint(sockaddr* addr);
		IPVersion getIPVersion();
		std::vector<uint8_t> getIPBytes();
		std::string getHostName();
		std::string getIPString();
		unsigned short getPort();
		sockaddr_in getSockaddrIPv4();
		std::string toString();
		void displayValues();
	private:
		IPVersion ipVersion = IPVersion::Unknown;
		std::string hostName;
		std::string ip_string;
		std::vector<uint8_t> ip_bytes;
		unsigned short port = 0;
	};
}