#pragma once
#include "IPVersion.h"
#include <string>
#include <vector>

namespace NetConnect {
	class IPEndpoint {
	public:
		IPEndpoint(const char* ip, unsigned short port);
		IPVersion getIPVersion();
		std::vector<uint8_t> getIPBytes();
		std::string getHostName();
		std::string getIPString();
		unsigned short getPort();
	private:
		IPVersion ipVersion = IPVersion::Unknown;
		std::string hostName;
		std::string ip_string;
		std::vector<uint8_t> ip_bytes;
		unsigned short port = 0;
	};
}