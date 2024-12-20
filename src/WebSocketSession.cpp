// WebSocketSession.cpp
#include "WebSocketSession.h"
#include "Logger.h"

// constructor initialization
WebSocketSession::WebSocketSession(tcp::socket socket, asio::ssl::context& ctx)
    : ws_(std::move(socket), ctx) {}


//starts the session by performing the handshake
void WebSocketSession::start() {
    // creates a shared prt to current object
    auto self = shared_from_this(); 
    // initiates an asynchronous SSL handshake with a lamda callback if successful calls do_accept()
    ws_.next_layer().async_handshake(asio::ssl::stream_base::server,
        [this, self](beast::error_code ec) {
            if (!ec) {
                do_accept();
            } else {
                // if fails, logs error message 
                Logger::instance().log("SSL handshake failed: " + ec.message());
            }
        });
}

// perform websocket handshake if successful call do read method
void WebSocketSession::do_accept() {
    auto self = shared_from_this();
    ws_.async_accept([this, self](beast::error_code ec) {
        if (!ec) {
            do_read();
        } else {
            Logger::instance().log("WebSocket accept failed: " + ec.message());
        }
    });
}

// reads data from the websocket 
void WebSocketSession::do_read() {
    auto self = shared_from_this();
    // initiates an async read operation
    ws_.async_read(buffer_, [this, self](beast::error_code ec, std::size_t bytes_transferred) {
        boost::ignore_unused(bytes_transferred);

        if (!ec) {
            std::string message = beast::buffers_to_string(buffer_.data());
            Logger::instance().log("Received: " + message);
            buffer_.consume(buffer_.size());
            do_write(message);
        } else {
            Logger::instance().log("Read: " + ec.message());
        }
    });
}

// writes data to the websocket
void WebSocketSession::do_write(const std::string& message) {
    auto self = shared_from_this();
    // initiates async write operation
    ws_.async_write(asio::buffer(message), [this, self](beast::error_code ec, std::size_t bytes_transferred) {
        boost::ignore_unused(bytes_transferred);

        if (!ec) {
            Logger::instance().log("Echoed: " + ec.message());
            do_read();
        } else {
            Logger::instance().log("Write failed: " + ec.message());
        }
    });
}
