UDP Network Communication Program
Description
This project demonstrates a UDP-based network communication system using a client-server model. The program consists of two components:

Client1: Sends messages to the server.
Client2: Receives messages from the client and displays them.
The system uses the UDP protocol for communication, making it lightweight and connectionless.

Features
Client: Reads user input and sends messages to the server.
Server: Listens for incoming messages and prints them to the console.
Supports termination with the command exit.
Prerequisites
Windows: Ensure you have MinGW or another GCC-compatible compiler installed.
Linux: GCC or any standard C++ compiler.
Both client and server must be run on the same machine or network for communication.
Compilation Instructions
Open a terminal or command prompt and navigate to the project directory.
Compile the programs:
Client1:
bash
Copy code
g++ Client1.cpp -o client -lws2_32
Client2:
bash
Copy code
g++ Client2.cpp -o server -lws2_32
Execution
Start the server first:

bash
Copy code
./server
This will make the server listen for incoming messages.

Start the client:

bash
Copy code
./client
Enter messages to send to the server. To terminate, type exit.

File Structure
graphql
Copy code
project/
├── Client1.cpp       # Client-side implementation
├── Client2.cpp       # Server-side implementation
├── UDPSocket.h       # Base UDP socket handling
├── UDPServer.h       # UDP server implementation
└── README.md         # This file
Notes
Ensure the client and server use the same IP and port for communication.
Messages are sent and received using the UDP protocol (connectionless).