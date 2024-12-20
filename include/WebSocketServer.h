#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <boost/asio.hpp>               //provides aync i/o func
#include <boost/beast.hpp>              //provides websocket HTTP func
#include <boost/asio/ssl.hpp>           //provides ssl func
#include "WebSocketSession.h"           

//namespace alias
namespace asio = boost::asio;
namespace beast = boost::beast;
using tcp = asio::ip::tcp;

//creating class to use Oops concept and hadling connection and SSL context
class WebSocketServer {
private:
    //accepts incoming TCP conn and referece of SSL context
    tcp::acceptor acceptor_;
    asio::ssl::context& context_;

    void do_accept();
public:
    //constructor initialization
    WebSocketServer(asio::io_context& ioc, asio::ssl::context& ctx, const tcp::endpoint& endpoint);
    // starts the server
    void run();

};

#endif // WEBSOCKETSERVER_H
