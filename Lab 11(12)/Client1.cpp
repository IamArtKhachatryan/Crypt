#include <iostream>
#include <string>
#include "UDPSocket.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8888

int main() {
    try {
        UDPSocket clientSocket;
        sockaddr_in serverAddress;

        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(SERVER_PORT);
        serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP);

        while (true) {
            std::string message;
            std::cout << "Enter a message to send (or type 'exit' to quit): ";
            std::getline(std::cin, message);

            if (message == "exit") {
                std::cout << "Exiting client.\n";
                break;
            }

            clientSocket.SendDatagram(message.c_str(), message.length(), &serverAddress, sizeof(serverAddress));
            std::cout << "Message sent to server: " << message << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Client error: " << e.what() << "\n";
    }

    return 0;
}
