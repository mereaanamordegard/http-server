#include "TCPServer.h"


bool TCPServer::listening(int maxConnections) {
	return ::listen(serverSocket, maxConnections) != SOCKET_ERROR;
}

bool TCPServer::bindServer() {
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket invalid." << std::endl;
        return false;
    }
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (ip == nullptr) {
        std::cout << "Binding to all interfaces on port: " << port << std::endl;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    else {
        inet_pton(AF_INET, ip, &addr.sin_addr);
        std::cout << "Binding to: " << ip << ":" << port << std::endl;
    }
    int result = bind(serverSocket, (sockaddr*)&addr, sizeof(addr));
    if (result == SOCKET_ERROR) {
        std::cerr << "Failed to binding socket:" << WSAGetLastError() << std::endl;
        return false;
    }
    else {
        std::cout << "Binding to port: " << port << std::endl;
    }
    return true;
}

SOCKET TCPServer::acceptConnections()
{
    SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
    }
    return clientSocket;
}

bool TCPServer::sendResponse(SOCKET clientSocket, const std::string& response) {
	int bytesSent = send(clientSocket, response.c_str(), response.length(), 0);
	if (bytesSent == SOCKET_ERROR) {
		std::cerr << "Failed: " << WSAGetLastError() << std::endl;
		closesocket(clientSocket);
		return false;
	}
	else {
		return true;
	}
}

std::string TCPServer::receiveRequest(SOCKET clientSocket)
{
    int bytesReceived = recv(clientSocket, BUFFER_SIZE, sizeof(BUFFER_SIZE) - 1, 0);
    if (bytesReceived > 0)
    {
        BUFFER_SIZE[bytesReceived] = '\0';
        return std::string(BUFFER_SIZE);
    }
    return "";
}

SOCKET TCPServer::getSocket() {
	return serverSocket;
}

const char* TCPServer::getIp()
{
	return ip;
}

int TCPServer::getPort() {
	return port;
}

