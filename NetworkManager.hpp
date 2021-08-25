#include "readerwriterqueue.h"
#include "Constants.hpp"
#include <thread>
#include <chrono>
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
        explicit NetworkManager(moodycamel::BlockingReaderWriterQueue<DataPacket> &dp) : rwq(dp)
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
                DataPacket dp(nullptr);
                rwq.wait_dequeue(dp); // listen for commands from gui thread


                std::cout << "GUI thread sent command" << std::endl;
            }
        }


        int receiveMessage()
        {

        }

    private:
        moodycamel::BlockingReaderWriterQueue<DataPacket> &rwq; // gui thread -> network thread

    };
}