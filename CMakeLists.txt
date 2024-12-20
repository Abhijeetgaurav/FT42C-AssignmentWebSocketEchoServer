cmake_minimum_required(VERSION 3.10)
project(SocketProgramming)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add executable for server
add_executable(WebSocketServer
    src/Logger.cpp
    src/main.cpp
    src/WebSocketServer.cpp
    src/WebSocketSession.cpp
)

# Add executable for client
add_executable(WebSocketClient
    src/WebSocketClient.cpp
)

# Link libraries
target_link_libraries(WebSocketServer
    pthread
    websockets
    ssl
    crypto
)

target_link_libraries(WebSocketClient
    pthread
    websockets
    ssl
    crypto
)

