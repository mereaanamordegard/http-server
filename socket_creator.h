#pragma once

#include <iostream>

#include "WinSock_Initialize.h"
class socket_creator
{
private:
	SOCKET godSocket;
	WinSock_Initialize& bootstrap;
public:
	socket_creator(WinSock_Initialize& bs) : godSocket(INVALID_SOCKET), bootstrap(bs) {};
	socket_creator(const socket_creator&) = delete;
	bool initialize();
	SOCKET createSocket(int af = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP);
	bool binding(SOCKET serverSocket, int port, const char* ip = nullptr);
	bool checkBinding(SOCKET sock);
};

