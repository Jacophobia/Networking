#pragma once
#include "SocketOptions.h"

#include "SocketHandle.h"
#include "PResult.h"
#include "IPVersion.h"
#include "IPEndpoint.h"

namespace NetConnect {
	class Socket {
	public:
		Socket(IPVersion ipVersion = IPVersion::IPv4, SocketHandle handle = INVALID_SOCKET);
		PResult create();
		PResult close();
		PResult bindEndpoint(IPEndpoint endpoint);
		PResult listenEndpoint(IPEndpoint endpoint, int backlog = 5);
		PResult acceptConnection(Socket& outSocket);
		PResult createConnection(IPEndpoint endpoint);
		SocketHandle getHandle();
		IPVersion getIPVersion();
	private:
		// Capital bool is actually an integer in the backend
		PResult setSocketOption(SocketOption option, BOOL value);
		IPVersion ipVersion = IPVersion::IPv4;
		SocketHandle handle = INVALID_SOCKET;
	};
}