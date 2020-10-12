#pragma once
#include "SDL2pp/SDL.hh"
#include "SDL2pp/Window.hh"
#include <experimental/optional>
#include "SDL2pp/SDL2pp.hh"
#include <SDL2/SDL2_gfxPrimitives.h>
// #include "SDL2/


namespace Pong { namespace Net {


class Game 
{
    public:
    Game();
    void run();
    private:
    void processEvents();
    void update();
    void render();
    private:
    SDL2pp::Window mWindow;


    
    
    
    
    
    
};

} }