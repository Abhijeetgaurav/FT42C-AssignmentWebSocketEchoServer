#ifndef WEBSOCKETSESSION_H
#define WEBSOCKETSESSION_H

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>
#include <memory>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace websocket = beast::websocket;
using tcp = asio::ip::tcp;
using ssl_socket = beast::ssl_stream<beast::tcp_stream>;

// class WebSocketSession inherits from std::enable_shared_from_this<WebSocketSession>, 
// enabling instances of WebSocketSession to create shared pointer to themselves. 
// it is useful for safe async operation
class WebSocketSession : public std::enable_shared_from_this<WebSocketSession> {
private:
    websocket::stream<ssl_socket> ws_;  // manages websocket conn over SSL stream
    beast::flat_buffer buffer_;        // holds incomming message

    void do_accept();      // handles SSL handshake
    void do_read();        // handles reading message from client
    void do_write(const std::string& message);      // handles writing message from client
public:
    //constructor
    WebSocketSession(tcp::socket socket, asio::ssl::context& ctx);
    //start session with necessary operation like SSL handshake and websocket handshake
    void start();

};

#endif // WEBSOCKETSESSION_H

