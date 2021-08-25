#include <iostream>
#include <thread>
#include <chrono>
#include <asio.hpp>
#include <gflags/gflags.h>
#include "readerwriterqueue.h"
#include "glog/logging.h"
#include "../State_generated.h"
#include <queue>

struct Message {
    std::string value;

    const char *getBytes() {
        return value.c_str();
    }
};

using message_handler = std::function<void(Message&&)>;
using error_handler = std::function<void(std::error_code)>;

void handle_message(Message&& msg) {
    LOG(INFO) << "I got:" << msg.value;
}

void handle_error(std::error_code ec) {
    LOG(INFO) << "Some one died";
}

class session : public std::enable_shared_from_this<session> {

    uint16_t id{};

public:
    bool isLive() {
        return socket.is_open();
    }

    explicit session(asio::ip::tcp::socket &&socket) : socket(std::move(socket)) {
    }

    uint16_t getID() const {
        return id;
    }

    void start(uint16_t uid, message_handler &&mh, error_handler &&eh) {
        do_msg = mh;
        do_error = eh;
        id = uid;
        do_read();
    }

    void do_read() {   // what is the benefit of using shared_from_this over &
        asio::async_read_until(socket, streambuf,
                               '\n',
                               [&, self = shared_from_this()](std::error_code error, std::size_t bytes_transferred) {
                                   if (!error) {
                                       std::stringstream message;
                                       message << socket.remote_endpoint(error) << ": "
                                               << std::istream(&streambuf).rdbuf();
                                       streambuf.consume(bytes_transferred);
                                       do_msg(Message{message.str()});
                                       LOG(INFO) << message.str();

                                       self->streambuf.consume(bytes_transferred);
                                       self->do_read();
                                   }

                               });

    }
    void write(Message msg){
        outgoing.push(msg);
        do_write();
    }
    void do_write() {
        auto self = this->shared_from_this(); // why would you do this?
        asio::async_write(socket, asio::buffer(outgoing.front().value),
                          [self, this](asio::error_code error, std::size_t bytes_transferred) {
                              if (!error) {
                                  self->outgoing.pop();
                                  if (!self->outgoing.empty()) {
                                      self->do_write();
                                  }
                              } else {
                                  self->socket.close(error);
                                  do_error(error);
                              }
                          });
    }



private:
    std::queue<Message> outgoing;
    asio::ip::tcp::socket socket;
    asio::streambuf streambuf;
    message_handler do_msg;
    error_handler do_error;
    std::queue<Message> incoming;
};

class server {
public:
    server(asio::io_context &io_context, std::uint16_t port)
            : io_context(io_context),
              acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {
    }

    void async_accept() {

        socket.emplace(io_context);

        acceptor.async_accept(*socket, [&](std::error_code error) {
            LOG(INFO) << "SUPP";
            if (!error) {

                std::shared_ptr<session> sp = std::make_shared<session>(std::move(*socket)); // totally moved
                sp->start(idCnt, handle_message,handle_error);
                idCnt++; // single threaded access only
                connections.push_back(std::move(sp));

                post_all(Message{"Someone Joined"});
                LOG(INFO) << "Client id:" << connections.back()->getID() << " Joined";
            }


            async_accept(); // add another
        });
    }
        void post_all(const Message& message)
        {
            for(auto& client : connections)
            {
                client->write(message);
            }
        }


private:
    std::vector<std::shared_ptr<session>> connections;
    asio::io_context &io_context;
    asio::ip::tcp::acceptor acceptor;
    std::optional<asio::ip::tcp::socket> socket;
    uint16_t idCnt{};
};

using namespace std::chrono_literals;

int main(int argc, char **argv) {

    gflags::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);
    fLB::FLAGS_alsologtostderr = true;
    // write these packets onto the queue
    // have a worker thread listening to the other side ready to handle the packet;
    asio::io_context ioContext;
    server s(ioContext, 8883);
    s.async_accept(); // add accept to context
    // when this accept call back is invoked it will push another async_accept onto the io context
    ioContext.run();
    // std::jthread th([&]() { // capture by reference
    //     ioContext.run();
    // }); // jthread is auto joined in destructor

    //    if(th.request_stop()){
    //        LOG(INFO) << "thread stopped";
    //        exit(0);
    //    }

    //    asio::thread_pool tp(4);
    //    asio::post(tp,[]())
    //    asio::thread_pool tp(2);

    //    asio::io_context io_context;
    //    server srv(io_context, 15001);
    //    srv.async_accept();
    //    io_context.run();
    return 0;
}