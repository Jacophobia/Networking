// Server Source Code

#include <IncludeMe.h>
#include <iostream>

int main() {
	if (NetConnect::Network::initialize()) {
		std::cout << "Winsock Successfully Initialized" << std::endl;

		NetConnect::IPEndpoint test("www.google.com", 8080);
		if (test.getIPVersion() == NetConnect::IPVersion::IPv4) {
			std::cout << "Hostname: " << test.getHostName() << std::endl;
			std::cout << "IP: " << test.getIPString() << std::endl;
			std::cout << "Port: " << test.getPort() << std::endl;
			std::cout << "IP Bytes: ";
			for (auto& digit : test.getIPBytes()) {
				std::cout << (int)digit << " ";
			}
			std::cout << std::endl;
		}
		else {
			std::cerr << "This is not an IPv4 address." << std::endl;
		}

		NetConnect::Socket socket;
		if (socket.Create() == NetConnect::PResult::P_Success) {
			std::cout << "Socket creation was successful" << std::endl;
			socket.Close();
		}
		else {
			std::cerr << "Failed to create Socket" << std::endl;

		}
	}
	NetConnect::Network::shutdown();
	return 0;
}