// Client Source Code

#include <IncludeMe.h>
#include <iostream>

int main() {
	if (NetConnect::Network::initialize()) {
		std::cout << "Winsock Successfully Initialized" << std::endl;
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