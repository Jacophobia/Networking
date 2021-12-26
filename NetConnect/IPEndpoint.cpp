#include "IPEndpoint.h"
#include <WS2tcpip.h>

namespace NetConnect {
	IPEndpoint::IPEndpoint(const char* ip, unsigned short port)
	{
		this->port = port;

		// internet address ipv4. If we were using IP version
		//  six we would use in_addr6
		in_addr addr; 

		// presentation to network
		int pton_result = inet_pton(AF_INET, ip, &addr);

		if (pton_result == 1) {
			if (addr.S_un.S_addr != INADDR_NONE) {
				ip_string = ip;
				hostName = ip;

				ip_bytes.resize(sizeof ULONG);

				memcpy(&ip_bytes[0], &addr.S_un.S_addr, sizeof ULONG);

				ipVersion = IPVersion::IPv4;
				return;
			}
		}

		// Try to get the ip address from a given host name. 
		//  Ex: Hostname www.google.com to 142.250.217.100
		addrinfo hints = {}; // This is like a filter used to narrow results
		hints.ai_family = AF_INET; // This tells it that we only want IPv4 addresses
		addrinfo* hostinfo = nullptr;
		int addrinfo_result = getaddrinfo(ip, NULL, &hints, &hostinfo);
		if (addrinfo_result == 0) {
			sockaddr_in * host_addr = reinterpret_cast<sockaddr_in*>(hostinfo->ai_addr);

			ip_string.resize(16);
			inet_ntop(AF_INET, &host_addr->sin_addr, &ip_string[0], 16);

			hostName = ip;

			ULONG ip_long = host_addr->sin_addr.S_un.S_addr;
			ip_bytes.resize(sizeof ULONG);
			memcpy(&ip_bytes[0], &ip_long, sizeof ULONG);

			ipVersion = IPVersion::IPv4;

			freeaddrinfo(hostinfo);
			return;
		}

		// Additional logic to resolve IPv6
	}

	IPVersion IPEndpoint::getIPVersion()
	{
		return ipVersion;
	}

	std::vector<uint8_t> IPEndpoint::getIPBytes()
	{
		return ip_bytes;
	}

	std::string IPEndpoint::getHostName()
	{
		return hostName;
	}

	std::string IPEndpoint::getIPString()
	{
		return ip_string;
	}

	unsigned short IPEndpoint::getPort()
	{
		return port;
	}
}