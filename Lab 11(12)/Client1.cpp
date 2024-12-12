#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include "UDPSocket.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8888

// Atomic flag to handle exiting the client gracefully
std::atomic<bool> exitClient(false);

void sendMessages(UDPSocket& clientSocket, sockaddr_in& serverAddress) {
    while (!exitClient) {
        std::string message;
        std::cout << "Enter a message to send (or type 'exit' to quit): ";
        std::getline(std::cin, message);

        if (message == "exit") {
            exitClient = true;
            std::cout << "Exiting client.\n";
            break;
        }

        clientSocket.SendDatagram(message.c_str(), message.length(), &serverAddress, sizeof(serverAddress));
        std::cout << "Message sent to server: " << message << "\n";
    }
}

void receiveMessages(UDPSocket& clientSocket) {
    char buffer[BUFLEN];
    sockaddr_in serverAddress;
    socklen_t serverAddressLen = sizeof(serverAddress);
    
    while (!exitClient) {
        int recvLen = clientSocket.ReceiveDatagram(buffer, BUFLEN, &serverAddress, &serverAddressLen);
        buffer[recvLen] = '\0'; // Null-terminate the received string
        std::cout << "Received message: " << buffer << "\n";
    }
}

int main() {
    try {
        UDPSocket clientSocket;
        sockaddr_in serverAddress;
        
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(SERVER_PORT);
        serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP);

        // Create threads for sending and receiving messages
        std::thread senderThread(sendMessages, std::ref(clientSocket), std::ref(serverAddress));
        std::thread receiverThread(receiveMessages, std::ref(clientSocket));

        // Join threads before exiting
        senderThread.join();
        receiverThread.join();
        
    } catch (const std::exception& e) {
        std::cerr << "Client error: " << e.what() << "\n";
    }

    return 0;
}
