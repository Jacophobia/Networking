#pragma once
namespace NetConnect {
	enum SocketOption {
		// This makes it so that it will not wait to send small packets 
		//  with large ones.
		TCP_NoDelay, 
	};
}