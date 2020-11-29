//
// Created by barriosj on 11/1/20.
//

#include "AutoPlayer.h"
#include "Ball.hpp"
void Pong::Net::AutoPlayer::Move(const Ball& mBall) {
    if (mBall.GetY() < GetY() + GetH() / 2) {
        MoveUp();
    }
    if (mBall.GetY() > GetY() + GetH() / 2) {
        MoveDown();
    }
}
Pong::Net::AutoPlayer::AutoPlayer(int x, int y, int width, int height, int speed) : Player(x, y, width, height,
                                                                                             speed) {


}
