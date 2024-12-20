#include "WebSocketServer.h"
#include "Logger.h"
#include <boost/asio/ssl.hpp>
#include <vector>
#include <thread>

// entry point taking command line argument
int main(int argc, char* argv[]) {
    //checking if the no of arguments are correct or not
    if (argc != 3) {
        std::cerr << "to run: server.cpp <ip address> <port>\n";
        return EXIT_FAILURE;
    }

    //converting cmd arg1 into ip adrress and other into port
    const auto address = asio::ip::make_address(argv[1]);
    const auto port = std::atoi(argv[2]);

    //io context creates I/O context for require I/O operations
    asio::io_context ioc;
    //creates a SSL context for Transport layer security
    asio::ssl::context ctx(asio::ssl::context::tlsv12);

    //loading server's certificate and private key from the specified files to enable SSL/TLS encryption prevent from imposter
    ctx.use_certificate_chain_file("/home/kpit/Desktop/skt_programming/certs/server.crt");
    ctx.use_private_key_file("/home/kpit/Desktop/skt_programming/certs/server.key", asio::ssl::context::pem);

    //server intialization, creating instance of WebSocketServer
    WebSocketServer server(ioc, ctx, tcp::endpoint{address, port});

    //logging and running the server
    Logger::instance().log("Starting server...");

    server.run();

    //implement thread pool to handle multiple connection/concurrency
    std::vector<std::thread> threads;
    for (size_t i = 0; i < std::thread::hardware_concurrency(); ++i) {
        threads.emplace_back([&ioc] {
            ioc.run();
        });
    }

    //waiting for all threads to finish execution
    for (auto& t : threads) {
        t.join();
    }

    return EXIT_SUCCESS;
}
