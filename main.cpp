#include <iostream>

#include "socket_creator.h"
#include "TCPServer.h"
int main() {

	WinSock_Initialize winSockBoot;
	socket_creator SocketManager(winSockBoot);
	TCPServer mainServer("127.0.0.1", 8080, SocketManager);
	
	
	mainServer.bindServer();
	SocketManager.checkBinding(mainServer.getSocket());
	mainServer.listening(SOMAXCONN);
	
	while (true) {

		SOCKET clientSocket = mainServer.acceptConnections();
		
		if (clientSocket == INVALID_SOCKET) {
			std::cerr << "INVALID SOCKET" << std::endl;
			continue;
		}

		std::string request = mainServer.receiveRequest(clientSocket);

		std::cout << "Received request:\n" << request << std::endl;

		std::string response =
			"HTTP/1.1 200 OK\r\n"
			"Content-Type: text/html\r\n"
			"Content-Length: 199\r\n"
			"Connection: close\r\n"
			"\r\n"
			"<html><body><h1>HeLlO WoRlD</h1> \r\n"
			"</body></html>";

		mainServer.sendResponse(clientSocket, response);

		closesocket(clientSocket);
	} 
	return 0;
}
