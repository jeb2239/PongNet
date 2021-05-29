#pragma once

#include <SDL2/SDL.h>
#include "SDL2pp/Texture.hh"
#include "State_generated.h"

namespace Pong::Net
{
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    const int CENTER_WIDTH = 5;

    const float MAX_ANGLE = 3.142 / 5.0; // 72 degrees

    const float BALL_MAXSPEED = 8.0f;
    const float BALL_ACCELERATE = 1.05f;
    const float BALL_INIT_SPEED = 4.0f;
    const int BALL_WIDTH = 10;
    const int BALL_HEIGHT = 10;

    float calc_angle(float y1, float y2, int height);

    void renderTexture(SDL2pp::Texture &tex, SDL2pp::Renderer &ren, int x, int y, int w = -1, int h = -1);
    void RestoreRect(SDL2pp::Rect &rect, const State::Rect *);

    void PrintKeyInfo(SDL_KeyboardEvent *key);

    struct DataPacket
    {
        DataPacket(Uint8 *buff) : buff(buff) {}
        Uint8 *buff;
    };
}
