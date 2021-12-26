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
		PResult Create();
		PResult Close();
		SocketHandle GetHandle();
		IPVersion GetIPVersion();
	private:
		// Capital bool is actually an integer in the backend
		PResult SetSocketOption(SocketOption option, BOOL value);
		IPVersion ipVersion = IPVersion::IPv4;
		SocketHandle handle = INVALID_SOCKET;
	};
}