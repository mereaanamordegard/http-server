#include "socket_creator.h"

SOCKET socket_creator::createSocket(int af, int type, int protocol) {
    if (!bootstrap.isInitialized()) {
        std::cerr << "Winsock is not initialized. Call initialize() first." << std::endl;
        return INVALID_SOCKET;
    }

    SOCKET newSocket = socket(af, type, protocol);
    if (newSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed. Error: " << WSAGetLastError() << std::endl;
        return INVALID_SOCKET;
    }
    else {
        std::cout << "Socket created successfully." << std::endl;
        return newSocket;
    }
}


bool socket_creator::checkBinding(SOCKET sock) {
    
    if (!bootstrap.isInitialized()) {
        std::cerr << "Winsock is not initialized. Call initialize() first." << std::endl;
        return false;
    }

    sockaddr_in addr;
    int addrLen = sizeof(addr);

    if (getsockname(sock, (sockaddr*)&addr, &addrLen) == 0) {
        char ipStr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &addr.sin_addr, ipStr, sizeof(ipStr));

        std::cout << "Socket Binding Info:" << std::endl;
        std::cout << "Socket: " << sock << std::endl;
        std::cout << "IP: " << ipStr << std::endl;
        std::cout << "Port: " << ntohs(addr.sin_port) << std::endl;
        return true;
    }
    else {
        std::cerr << "Socket is not bound. Error: " << WSAGetLastError() << std::endl;
        return false;
    }
}