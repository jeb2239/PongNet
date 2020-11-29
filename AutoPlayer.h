#pragma once

#include "Player.hpp"

namespace Pong::Net {
    class AutoPlayer : public Player {
    public:

         AutoPlayer(int x, int y, int width, int height, int speed);

        void Move(const Ball& b) override;


    };
}