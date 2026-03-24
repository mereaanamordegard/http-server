#pragma once

#include <WinSock2.h>
#include <iostream>
#include "socket_creator.h"

class TCPServer
{
private:
	const char* ip;
	int port;
	char BUFFER_SIZE[4096];
	sockaddr_in serverAddr;
	SOCKET serverSocket;

public:
	TCPServer(const char* ipAddress, int portNumber, socket_creator& creator) :
		ip(ipAddress),
		port(portNumber),
		serverSocket(creator.createSocket())
	{
	}

	~TCPServer() {
		if (serverSocket != INVALID_SOCKET) {
			closesocket(serverSocket);
		}
	}

	bool bindServer();
	bool listening(int maxConnections);
	SOCKET acceptConnections();
	bool sendResponse(SOCKET clientSocket, const std::string& response);
	std::string receiveRequest(SOCKET clientSocket);

	SOCKET getSocket();
	const char* getIp();
	int getPort();
	char* getBUFFERsize();
};
