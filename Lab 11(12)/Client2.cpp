#include <iostream>
#include "UDPServer.h"
#define BUFLEN 1024

#define SERVER_PORT 8888

int main() {
    try {
        UDPServer server(SERVER_PORT);
        char buffer[BUFLEN];
        sockaddr_in clientAddress;
        socklen_t clientAddressLen = sizeof(clientAddress);

        std::cout << "Server listening on port " << SERVER_PORT << "...\n";

        while (true) {
            // Receive message
            int recvLen = server.ReceiveDatagram(buffer, BUFLEN, &clientAddress, &clientAddressLen);
            buffer[recvLen] = '\0'; // Null-terminate the received string

            std::cout << "Received message: " << buffer << "\n";

            if (std::string(buffer) == "exit") {
                std::cout << "Client requested to exit. Stopping server.\n";
                break;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << "\n";
    }

    return 0;
}
