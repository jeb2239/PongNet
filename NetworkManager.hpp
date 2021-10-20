#include "readerwriterqueue.h"
#include "Constants.hpp"
#include <thread>
#include <chrono>
#include <span>
#include "asio.hpp"
namespace Pong::Net
{
    class NetworkManager
    {
    public:
    // establish a connection with player - sync of start of game estimate
    // state update udp -- send the last 3 copies of the worlds every frame every other frame
    // circular buff
    // single producer
    // tcp is commands
        explicit NetworkManager(moodycamel::BlockingReaderWriterQueue<std::vector<uint8_t>> &dp) : rwq(dp)
        {

        }

        int init()
        {

            // using namespace std::literals::chrono_literals;
            asio::io_context io_ctx;
            asio::ip::tcp::socket sock(io_ctx);
            asio::ip::tcp::resolver resolver(io_ctx);
            
            while (true) // send event info to player , my pack need to figure circular thread safe 
            {
                std::span<uint8_t> v;
                rwq.wait_dequeue(v); // listen for commands from gui thread
                sock.connect()

                std::cout << "GUI thread sent command" << std::endl;
            }
        }


        int receiveMessage()
        {

        }

    private:
        moodycamel::BlockingReaderWriterQueue<std::vector<uint8_t>> &rwq; // gui thread -> network thread

    };
}