#pragma once

#include <WinSock2.h>
#include <iostream>
#include "WinSock_Initialize.h"

class TCPServer
{
private:
	const char* ip;
	int port;
	char BUFFER_SIZE[4096];
	sockaddr_in serverAddr;
	WinSock_Initialize& bootstrap;
	SOCKET serverSocket;

public:
	
	TCPServer(const char* ipAddress, int portNumber, WinSock_Initialize& boot) :
		ip(ipAddress),
		port(portNumber),
		bootstrap(boot) 
{
		serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	};
	
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

