#include "WinSock_Initialize.h"

WinSock_Initialize::WinSock_Initialize() : initialized(false) {
	std::cout << "Initializing Winsock..." << std::endl;
	initialize();
};

WinSock_Initialize::~WinSock_Initialize() {
	cleanUp();
}

bool WinSock_Initialize::initialize() {
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock" << std::endl;
        return false;
    }
    initialized = true;
    return true;
}

bool WinSock_Initialize::cleanUp() {
    WSACleanup();
    initialized = false;
    return true;
}
bool WinSock_Initialize::isInitialized()  {
    return initialized;
}