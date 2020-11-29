#include "Constants.hpp"
#include "SDL2pp/Renderer.hh"
#include "glog/logging.h"
float Pong::Net::calc_angle(float y1, float y2, int height) {
    float rely = y1 + height / 2 - y2;
    rely /= height / 2.0; // Normalise
    return rely * MAX_ANGLE;
}

void Pong::Net::renderTexture(SDL2pp::Texture &tex, SDL2pp::Renderer &ren, int x, int y, int w, int h) {
    SDL_Texture *tx = tex.Get();
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;

    // If no width and height are specified, use the texture's actual width and height
    if (w == -1 || h == -1)
        SDL_QueryTexture(tx, nullptr, nullptr, &dest.w, &dest.h);

    SDL_RenderCopy(ren.Get(), tx, nullptr, &dest);
}

void Pong::Net::PrintKeyInfo(SDL_KeyboardEvent *key) {
    LOG(INFO) <<"Name: "<< SDL_GetKeyName(key->keysym.sym);
}

void Pong::Net::RestoreRect(SDL2pp::Rect &rect, const Pong::Net::State::Rect *r) {
    rect.SetY(r->y());
    rect.SetX(r->x());
    rect.SetH(r->h());
    rect.SetW(r->w());
}
