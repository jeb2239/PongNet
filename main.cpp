#include "Game.hpp"
#include "SDL.h"
#include "SDL2pp/Renderer.hh"
#include "gflags/gflags.h"
#include "glog/logging.h"
#include "Concepts.hpp"
#include "readerwriterqueue.h"
#include "NetworkManager.hpp"
#include "Constants.hpp"
#include <thread>
DEFINE_string(saveFile,"","file to use for restoring game state");

int main(int argc, char **argv)
{
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);
    SDL2pp::SDL sdl(SDL_INIT_EVERYTHING);
    //packet of game state there should be a timestamp
    /*
    milliseconds 
    paddle movement should be variable -starts acceleration y''' order goes up and stops
    */
    LOG(INFO) << "booting game";
    moodycamel::BlockingReaderWriterQueue<Pong::Net::DataPacket> rwq;
    Pong::Net::Game g(rwq);
    if (!FLAGS_saveFile.empty()){
        g.loadSaveState(FLAGS_saveFile);
    }
    // std::thread guiThread([&](){
    //     g.run(); // game loop
    // });
    
    // std::thread networkThread([&](){
    //     Pong::Net::NetworkManager nmgr(rwq); // should block
    //     nmgr.init(); //network loop
    // });
    // networkThread.detach();
    g.run();
    
    

    
       
}