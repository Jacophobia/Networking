#include "Socket.h"

#include <assert.h>
#include <iostream>

namespace NetConnect {

	Socket::Socket(IPVersion ipVersion, SocketHandle handle) :
		ipVersion(ipVersion), handle(handle)
	{
		assert(ipVersion == IPVersion::IPv4);
	}

	PResult Socket::create()
	{
		assert(ipVersion == IPVersion::IPv4);

		if (handle != INVALID_SOCKET) {
			std::cerr << "Socket Already Created" << std::endl;
			return PResult::P_NotYetImplemented;
		}

		handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (handle == INVALID_SOCKET) {
			std::cerr << "Unable to retreive socket handle" << std::endl;
			return PResult::P_NotYetImplemented;
		}

		if (setSocketOption(SocketOption::TCP_NoDelay, TRUE) != PResult::P_Success) {
			return PResult::P_NotYetImplemented;
		}

		return PResult::P_Success;
	}

	PResult Socket::close()
	{
		if (handle == INVALID_SOCKET) {
			return PResult::P_NotYetImplemented;
		}
		int result = closesocket(handle);
		if (result != 0) {
			int errorCode = WSAGetLastError();
			std::cerr << "Error code " << errorCode << " Received." << std::endl;
			return PResult::P_NotYetImplemented;
		}

		handle = INVALID_SOCKET;
		return PResult::P_Success;
	}

	PResult Socket::bindEndpoint(IPEndpoint endpoint)
	{
		sockaddr_in addr = endpoint.getSockaddrIPv4();
		
		int bind_result = bind(handle, (sockaddr*) &addr, sizeof sockaddr_in);
		if (bind_result != 0) {
			int bind_error = WSAGetLastError();
			return PResult::P_NotYetImplemented;
		}
		return PResult::P_Success;
	}

	PResult Socket::listenEndpoint(IPEndpoint endpoint, int backlog)
	{
		if (bindEndpoint(endpoint) != PResult::P_Success) {
			return PResult::P_NotYetImplemented;
		}

		int listen_result = listen(handle, backlog);

		if (listen_result != 0) {
			int listen_error = WSAGetLastError();
			std::cerr
				<< "An error occurred while attempint to listen to endpoint"
				<< "Error Code: " << listen_error << std::endl;
			return PResult::P_NotYetImplemented;
		}
		return PResult::P_Success;
	}

	PResult Socket::acceptConnection(Socket& outSocket)
	{
		sockaddr_in addr = {};
		int len = sizeof sockaddr_in;
		SocketHandle acceptedConnectionHandle = accept(handle, (sockaddr*)&addr, &len);
		if (acceptedConnectionHandle == INVALID_SOCKET) {
			int accConHan_error = WSAGetLastError();
			std::cerr
				<< "Error accepting connection handle. Error code "
				<< accConHan_error << std::endl;
			return PResult::P_NotYetImplemented;
		}

		IPEndpoint newConnectionEndpoint((sockaddr*)&addr);

		std::cout << "New Connection Created" << std::endl;
		newConnectionEndpoint.displayValues();

		outSocket = Socket(IPVersion::IPv4, acceptedConnectionHandle);
		return PResult::P_Success;
	}

	PResult Socket::createConnection(IPEndpoint endpoint)
	{
		sockaddr_in addr = endpoint.getSockaddrIPv4();
		int connection_result = connect(handle, (sockaddr*)&addr, sizeof sockaddr_in);

		if (connection_result != 0) {
			int connection_error = WSAGetLastError();
			std::cerr
				<< "Error forming a connection. Error Code "
				<< connection_error << std::endl;
			return PResult::P_NotYetImplemented;
		}
		return PResult::P_Success;
	}

	SocketHandle Socket::getHandle()
	{
		return handle;
	}

	IPVersion Socket::getIPVersion()
	{
		return ipVersion;
	}
	PResult Socket::setSocketOption(SocketOption option, BOOL value)
	{
		int sockoptResult = 0;
		switch (option)
		{
		case NetConnect::TCP_NoDelay:
			sockoptResult = setsockopt(handle, IPPROTO_TCP, TCP_NODELAY, (const char*)&value, sizeof value);
			break;
		default:
			return PResult::P_NotYetImplemented;
		}

		if (sockoptResult != 0) {
			int errorCode = WSAGetLastError();
			std::cerr << "Unable to set socket options: Error Code " << errorCode << std::endl;
			return PResult::P_NotYetImplemented;
		}
		return PResult::P_Success;
	}
}