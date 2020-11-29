#include "Game.hpp"
#include "SDL.h"
#include "SDL2pp/Renderer.hh"
#include "gflags/gflags.h"
#include "glog/logging.h"
#include "Concepts.hpp"

DEFINE_string(saveFile,"","file to use for restoring game state");

int main(int argc, char **argv)
{
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);
    SDL2pp::SDL sdl(SDL_INIT_EVERYTHING);

    
    LOG(INFO) << "booting game";
    Pong::Net::Game g;
    if (!FLAGS_saveFile.empty()){
        g.loadSaveState(FLAGS_saveFile);
    }

    g.run();
       
}