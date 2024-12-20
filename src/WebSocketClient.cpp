#include "root_certificate.hpp"

#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

namespace beast = boost::beast;         
namespace http = beast::http;           
namespace websocket = beast::websocket; 
namespace net = boost::asio;            
namespace ssl = boost::asio::ssl;       
using tcp = boost::asio::ip::tcp;       

// sends a WebSocket message and prints the response
int main(int argc, char** argv)
{
    try
    {
        // check command line arguments
        if(argc != 4)
        {
            std::cerr <<
                "to run: client.cpp <ip address> <port> <message>";
            return EXIT_FAILURE;
        }
        std::string host = argv[1];
        auto const  port = argv[2];
        auto const  text = argv[3];

        // the io_context is required for all I/O
        net::io_context ioc;

        // the SSL context is required, and holds certificates
        ssl::context ctx{ssl::context::tlsv12_client};

        // this holds the root certificate used for verification
        load_root_certificates(ctx);

        // these objects perform our I/O
        tcp::resolver resolver{ioc};
        websocket::stream<beast::ssl_stream<tcp::socket>> ws{ioc, ctx};

        // look up the domain name
        auto const results = resolver.resolve(host, port);

        // make the connection on the IP address we get from a lookup
        auto ep = net::connect(get_lowest_layer(ws), results);

        // set SNI Hostname (many hosts need this to handshake successfully)
        if(! SSL_set_tlsext_host_name(ws.next_layer().native_handle(), host.c_str()))
            throw beast::system_error(
                beast::error_code(
                    static_cast<int>(::ERR_get_error()),
                    net::error::get_ssl_category()),
                "Failed to set SNI Hostname");

        // update the host string. This will provide the value of the
        // Host HTTP header during the WebSocket handshake.
        host += ':' + std::to_string(ep.port());

        // perform the SSL handshake
        ws.next_layer().handshake(ssl::stream_base::client);

        // set a decorator to change the User-Agent of the handshake
        ws.set_option(websocket::stream_base::decorator(
            [](websocket::request_type& req)
            {
                req.set(http::field::user_agent,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-client-coro");
            }));

        // perform the websocket handshake
        ws.handshake(host, "/");

        // send the message
        ws.write(net::buffer(std::string(text)));

        // this buffer will hold the incoming message
        beast::flat_buffer buffer;

        // read a message into our buffer
        ws.read(buffer);

        // close the WebSocket connection
        ws.close(websocket::close_code::normal);

        // if we get here then the connection is closed gracefully

        // the make_printable() function helps print a ConstBufferSequence
        std::cout << beast::make_printable(buffer.data()) << std::endl;
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
