#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib") 
#include <iostream>
class WinSock_Initialize
{
private:
	bool initialized;
	WSADATA wsaData;
	
public:
	WinSock_Initialize();
	~WinSock_Initialize();
	bool initialize();
	bool cleanUp();
	bool isInitialized();
};

