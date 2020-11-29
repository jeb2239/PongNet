#pragma once


#include "Player.hpp"

namespace Pong::Net {
    class HumanPlayer : public Player {
    public:

        HumanPlayer(int x, int y, int width, int height, int speed);

        void Move(const Ball& b) override;

    private:
        const Uint8* keystates;
    };
}