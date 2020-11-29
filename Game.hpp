#pragma once

#include "SDL2pp/AudioDevice.hh"
#include "SDL2pp/Renderer.hh"
#include "SDL2pp/SDL.hh"
#include "SDL2pp/Window.hh"
#include <experimental/optional>
#include "SDL2pp/SDL2pp.hh"
#include <SDL2/SDL2_gfxPrimitives.h>
#include "Constants.hpp"
#include "Ball.hpp"
#include "Player.hpp"
#include "HumanPlayer.hpp"
#include "AutoPlayer.h"
#include "State_generated.h"
#include "gflags/gflags.h"


namespace Pong::Net {
    class Game {
    public:
        Game();

        void run();
        void loadSaveState(const std::string&);
    private:
        void processEvents();

        void update();

        void render();

        void stateSave();

    private:
        SDL2pp::Window mWindow;
        Ball mBall;
        bool mRunning;
        SDL2pp::Renderer mRenderer;
        SDL2pp::Texture mBoardTexture;
        HumanPlayer p1;
        AutoPlayer p2;
        int frames;
        int fps;
    };

} // namespace Pong