#include <iostream>
#include <thread>
#include "UDPServer.h"
#include "UDPCommon.h"

#define SERVER_PORT 8888

void handleClient(UDPServer& server, sockaddr_in& clientAddress, socklen_t clientAddressLen) {
    char buffer[BUFLEN];
    int recvLen = server.ReceiveDatagram(buffer, BUFLEN, &clientAddress, &clientAddressLen);
    buffer[recvLen] = '\0'; // Null-terminate the received string

    std::cout << "Received message: " << buffer << "\n";

    if (std::string(buffer) == "exit") {
        std::cout << "Client requested to exit. Stopping server.\n";
    }
}

int main() {
    try {
        UDPServer server(SERVER_PORT);
        char buffer[BUFLEN];
        sockaddr_in clientAddress;
        socklen_t clientAddressLen = sizeof(clientAddress);

        std::cout << "Server listening on port " << SERVER_PORT << "...\n";

        while (true) {
            // Handle each incoming datagram in a separate thread
            std::thread clientThread(handleClient, std::ref(server), std::ref(clientAddress), clientAddressLen);
            clientThread.detach(); // Detach to allow the server to handle other clients

            // You can implement additional logic here for server-side communication (e.g., broadcasting responses)
        }
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << "\n";
    }

    return 0;
}
