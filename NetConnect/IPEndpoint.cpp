#include "IPEndpoint.h"
#include <assert.h>
#include <iostream>

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

	IPEndpoint::IPEndpoint(sockaddr* addr)
	{
		assert(addr->sa_family == AF_INET);

		sockaddr_in* addrv4 = reinterpret_cast<sockaddr_in*>(addr);
		ipVersion = IPVersion::IPv4;
		// network to host-byte-order short
		port = ntohs(addrv4->sin_port);
		ip_bytes.resize(sizeof ULONG);
		memcpy(&ip_bytes[0], &addrv4->sin_addr, sizeof ULONG);

		ip_string.resize(16);
		inet_ntop(AF_INET, &addrv4->sin_addr, &ip_string[0], 16);

		hostName = ip_string;

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
	sockaddr_in IPEndpoint::getSockaddrIPv4()
	{
		assert(ipVersion == IPVersion::IPv4);
		sockaddr_in addr = {};
		addr.sin_family = AF_INET; // standard for IPv4
		memcpy(&addr.sin_addr, &ip_bytes[0], sizeof ULONG);
		// host to network-byte-order short (for long do l instead of s)
		addr.sin_port = htons(port); 

		return addr;
	}
	std::string IPEndpoint::toString()
	{
		std::string str_IPEndpoint;
		switch (ipVersion) {
		case IPVersion::IPv4:
			str_IPEndpoint.append("IP Version 4\n");
			break;
		case IPVersion::IPv6:
			str_IPEndpoint.append("IP Version 6\n");
			break;
		default:
			str_IPEndpoint.append("Never Seen This IP Version\n");
			break;
		}
		str_IPEndpoint.append(
			"Host Name: " + hostName +
			"\nIP: " + ip_string +
			"\nIP Bytes: " + "\n"
		);
		for (auto& byte : ip_bytes) {
			//str_IPEndpoint.append((int)byte + "\n");
			str_IPEndpoint.push_back(byte + 47);
		}
		str_IPEndpoint.append("\n");
		return str_IPEndpoint;
	}
	void IPEndpoint::displayValues()
	{
		std::string str_IPEndpoint;
		switch (ipVersion) {
		case IPVersion::IPv4:
			std::cout
				<< "IP Version 4" << std::endl;
			break;
		case IPVersion::IPv6:
			std::cout
				<< "IP Version 6" << std::endl;
			break;
		default:
			std::cout
				<< "Never Seen This IP Version" << std::endl;
			break;
		}
		std::cout
			<< "Host Name: " << hostName << std::endl
			<< "IP: " << ip_string << std::endl
			<< "IP Bytes: ";
		for (auto& byte : ip_bytes) {
			std::cout
				<< (int)byte << " ";
		}
		std::cout
			<< std::endl;
	}
}