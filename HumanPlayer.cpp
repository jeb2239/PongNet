//
// Created by barriosj on 11/10/20.
//

#include "HumanPlayer.hpp"

void Pong::Net::HumanPlayer::Move(const Ball &b) {

    if (keystates[SDL_SCANCODE_UP])
        MoveUp();
    if (keystates[SDL_SCANCODE_DOWN])
        MoveDown();
}

Pong::Net::HumanPlayer::HumanPlayer(int x, int y, int width, int height, int speed) : Player(x, y, width, height,
                                                                                             speed) {

    keystates = SDL_GetKeyboardState(nullptr);
}


