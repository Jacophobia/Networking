// Server Source Code

#include <IncludeMe.h>
#include <iostream>

int main() {
	if (NetConnect::Network::initialize()) {
		std::cout << "Winsock Successfully Initialized" << std::endl;

		// Below is a test that can be used to see if our program can 
		//  find an ip address using a given host name.
		//NetConnect::IPEndpoint test("www.google.com", 8080);
		//if (test.getIPVersion() == NetConnect::IPVersion::IPv4) {
		//	std::cout << "Hostname: " << test.getHostName() << std::endl;
		//	std::cout << "IP: " << test.getIPString() << std::endl;
		//	std::cout << "Port: " << test.getPort() << std::endl;
		//	std::cout << "IP Bytes: ";
		//	for (auto& digit : test.getIPBytes()) {
		//		std::cout << (int)digit << " ";
		//	}
		//	std::cout << std::endl;
		//}
		//else {
		//	std::cerr << "This is not an IPv4 address." << std::endl;
		//}

		// When we want to connect to our server. We need to open a socket. If
		//  "127.0.0.1" is used as our socket address than only programs on our
		//  device will be able to connect. This is good for testing. Otherwise
		//  we need to find out what our network address on our router is and
		//  use that. We can also use "0.0.0.0" for any outside device to be 
		//  able to connect to us. 

		NetConnect::Socket socket;
		if (socket.create() == NetConnect::PResult::P_Success) {
			std::cout << "Socket creation was successful" << std::endl;
			unsigned short port_addr = 4790;
			if (socket.listenEndpoint(NetConnect::IPEndpoint("127.0.0.1", port_addr)) == NetConnect::PResult::P_Success) {
				std::cout 
					<< "Socket successfully bound to port " 
					<< port_addr << ". Listening..."
					<< std::endl;
				NetConnect::Socket newConnection;
				if (socket.acceptConnection(newConnection) == NetConnect::PResult::P_Success) {
					std::cout
						<< "Successfully accepted new connection"
						<< std::endl;
					newConnection.close();
				}
			}
			else {
				std::cerr 
					<< "Unable to listen on port " 
					<< port_addr 
					<< std::endl;
			}
			socket.close();
		}
		else {
			std::cerr << "Failed to create Socket" << std::endl;

		}
	}
	NetConnect::Network::shutdown();
	return 0;
}