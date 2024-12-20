#include "WebSocketServer.h"
#include "Logger.h"

// constructor intialization
WebSocketServer::WebSocketServer(asio::io_context& ioc, asio::ssl::context& ctx, const tcp::endpoint& endpoint)
    : acceptor_(ioc, endpoint), context_(ctx) {}

void WebSocketServer::run() {
    // start accepting connections
    do_accept();
}

// manages asyc acceptiance of incoming conn.
void WebSocketServer::do_accept() {
    acceptor_.async_accept([this](beast::error_code ec, tcp::socket socket) {
        if (!ec) {
            // if no error shows client connected
            Logger::instance().log("Client connected.");
            // create a shared pointer for a new WebSocket session
            // transferring ownership of the socket using std::move, and start the session
            std::make_shared<WebSocketSession>(std::move(socket), context_)->start();
        } else {
            // if error, log it
            Logger::instance().log("Accept failed: " + ec.message());
        }

        // recursive calling do_accept() method to continue accepting multiple connection
        do_accept();
    });
}
