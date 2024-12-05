#pragma once

#ifdef _WIN32
    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib")
    using SOCKET_TYPE = SOCKET;
    typedef int socklen_t; // Define socklen_t for Windows
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <sys/types.h> // Ensure this is included for socklen_t
    #define SOCKET_TYPE int
#endif

#include <iostream>
#include <stdexcept>
#include <cstring>

class UDPSocket {
protected:
    SOCKET_TYPE socket_fd;

    static void InitializeWinsock() {
        #ifdef _WIN32
        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
            throw std::runtime_error("Winsock initialization failed");
        }
        #endif
    }

public:
    UDPSocket() {
        #ifdef _WIN32
        InitializeWinsock();
        #endif
        socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (socket_fd < 0) {
            throw std::runtime_error("Socket creation failed");
        }
    }

    virtual ~UDPSocket() {
        #ifdef _WIN32
        closesocket(socket_fd);
        WSACleanup();
        #else
        close(socket_fd);
        #endif
    }

    void SendDatagram(const char* message, int messageLen, struct sockaddr_in* dest, int destLen) {
        if (sendto(socket_fd, message, messageLen, 0, (struct sockaddr*)dest, destLen) < 0) {
            throw std::runtime_error("Send failed");
        }
    }

    int ReceiveDatagram(char* buffer, int bufferLen, struct sockaddr_in* src, socklen_t* srcLen) {
        int recvLen = recvfrom(socket_fd, buffer, bufferLen, 0, (struct sockaddr*)src, srcLen);
        if (recvLen < 0) {
            throw std::runtime_error("Receive failed");
        }
        return recvLen;
    }
};
