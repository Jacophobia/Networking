// Client Source Code

#include <IncludeMe.h>
#include <iostream>

int main() {
	if (NetConnect::Network::initialize()) {
		std::cout << "Winsock Successfully Initialized" << std::endl;
		NetConnect::Socket socket;
		if (socket.create() == NetConnect::PResult::P_Success) {
			std::cout << "Socket creation was successful" << std::endl;
			if (socket.createConnection(NetConnect::IPEndpoint("127.0.0.1", 4790)) == NetConnect::PResult::P_Success) {
				std::cout
					<< "Successfully connected to server"
					<< std::endl;
			}
			else {
				std::cout
					<< "Unable to connect to server"
					<< std::endl;
			}
			socket.close();
		}
		else {
			std::cerr << "Failed to create Socket" << std::endl;

		}
	}
	NetConnect::Network::shutdown();
	system("pause");
	return 0;
}