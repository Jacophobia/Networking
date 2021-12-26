#include "Socket.h"

#include <assert.h>
#include <iostream>

namespace NetConnect {

	Socket::Socket(IPVersion ipVersion, SocketHandle handle) :
		ipVersion(ipVersion), handle(handle)
	{
		assert(ipVersion == IPVersion::IPv4);
	}

	PResult Socket::Create()
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

		if (SetSocketOption(SocketOption::TCP_NoDelay, TRUE) != PResult::P_Success) {
			return PResult::P_NotYetImplemented;
		}

		return PResult::P_Success;
	}

	PResult Socket::Close()
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

	SocketHandle Socket::GetHandle()
	{
		return handle;
	}

	IPVersion Socket::GetIPVersion()
	{
		return ipVersion;
	}
	PResult Socket::SetSocketOption(SocketOption option, BOOL value)
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