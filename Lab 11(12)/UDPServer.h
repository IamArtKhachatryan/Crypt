#pragma once
#include "UDPSocket.h"

class UDPServer : public UDPSocket {
private:
    struct sockaddr_in serverAddress;

public:
    UDPServer(unsigned short port) {
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(port);
        serverAddress.sin_addr.s_addr = INADDR_ANY;

        if (bind(socket_fd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
            throw std::runtime_error("Bind failed");
        }
    }
};
