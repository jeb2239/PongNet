#pragma once
#include <asio.hpp>



namespace Pong::Net::Server {
    class GameServer {
    public:
        // Need to pass by reference b/c copy constructor is deleted
        explicit GameServer(asio::io_context& iosvc);
        void runForever();
    private:

        
        asio::io_context& ioctx;
        asio::ip::tcp::socket server_socket;

    };
}