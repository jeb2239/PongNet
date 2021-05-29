#include <asio/execution.hpp>
#include <asio/static_thread_pool.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <asio.hpp>
#include <asio/static_thread_pool.hpp>
#include "readerwriterqueue.h"

#include "../State_generated.h"
class session : public std::enable_shared_from_this<session> {
public:

    session(asio::ip::tcp::socket &&socket)
            : socket(std::move(socket)) {

    }

    void start() {
        asio::async_read_until(socket, streambuf,
                               '\n', [self = shared_from_this()]
                                       (std::error_code error, std::size_t bytes_transferred) {

                    std::cout << std::istream(&self->streambuf).rdbuf();

                });


    }

private:

    asio::ip::tcp::socket socket;
    asio::streambuf streambuf;
};

class server {
public:

    server(asio::io_context &io_context, std::uint16_t port)
            : io_context(io_context),
            acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)), tp(1) {
    }

    void async_accept() {
        socket.emplace(io_context);

        acceptor.async_accept(*socket, [&](std::error_code error) {
            std::make_shared<session>(std::move(*socket))->start();
             // this is where the loop comes from
        });
    }

private:

    asio::io_context &io_context;
    asio::ip::tcp::acceptor acceptor;
    asio::thread_pool tp;
    std::optional<asio::ip::tcp::socket> socket;
    moodycamel::BlockingReaderWriterQueue<Pong::Net::State::Packet> workq;
};

using namespace std::chrono_literals;
using myint = int;

int main() {
    moodycamel::BlockingReaderWriterQueue<Pong::Net::State::Packet> bq; // write these packets onto the queue
    // have a worker thread listening to the other side ready to handle the packet;
    asio::io_context ioContext;
    

    server s(ioContext,8883);
    s.async_accept();
    ioContext.run();

//    asio::thread_pool tp(4);
//    asio::post(tp,[]())
//    asio::thread_pool tp(2);

      
    
//    asio::io_context io_context;
//    server srv(io_context, 15001);
//    srv.async_accept();
//    io_context.run();
    return 0;
}