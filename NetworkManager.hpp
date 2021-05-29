#include "readerwriterqueue.h"
#include "Constants.hpp"
#include <thread>
#include <chrono>

namespace Pong::Net
{
    class NetworkManager
    {
        public:
        NetworkManager(moodycamel::BlockingReaderWriterQueue<DataPacket> &dp) : rwq(dp)
        {
        }

        int init()
        {
             using namespace std::literals::chrono_literals;

            while (true)
            {   
                DataPacket dp(nullptr);
                rwq.wait_dequeue(dp); // listen for commands from gui thread
                
                std::cout << "GUI thread sent command" << std::endl;
            }
        }

    private:
        moodycamel::BlockingReaderWriterQueue<DataPacket> &rwq;
    };
}