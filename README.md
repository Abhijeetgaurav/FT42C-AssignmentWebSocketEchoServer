**Socket Programming**
This project demonstrates socket programming using WebSockets with Boost.Beast library. It includes a WebSocket server and client, both using Boost libraries for asynchronous Input/Output.

Project: Created a secure WebSocket-based echo server using c++(Boost.Beast) library in Linux OS.

A websocket-based echo server is a full duplex communication system where both the client and server can send data to each other.The primary function of an echo server is to revieve message from client and send back the same messages, effectively "echoing" them.


**Install Dependencies**
sudo apt-get install libboost-all-dev libssl-dev libwebsockets-dev cmake

**Building the Project**
1.Clone the repository
git clone <repository_url>
cd socket_programming

2.Create a build directory
mkdir build
cd build

3.Run CMake:
cmake ..

4.Build the project:
make

5.Run the project:
Server
    ./WebSocketServer <ip> <port>

Client
    ./WebSocketClient <ip> <port> <message>

