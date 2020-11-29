#pragma once

#include "SDL2pp/Renderer.hh"
#include "SDL2pp/Rect.hh"
#include "SDL2pp/SDL.hh"
#include "Constants.hpp"
#include "State_generated.h"

namespace Pong::Net {
    class Ball;
    class Player {
    public:
        Player(int x, int y, int width, int height, int speed) :
        mPos(x, y, width, height), mScore(0), mSpeed(speed) {

        }

        int GetX() const {
            return mPos.GetX();
        }

        int GetY() const {
            return mPos.GetY();
        }

        int GetH() const {
            return mPos.GetH();
        }

        int GetW() const {
            return mPos.GetW();
        }

        int GetScore() const {
            return mScore;
        }

        void Scored() {
            mScore += 1;
        }

        void MoveUp() {
            mPos.y -= mSpeed;
        }

        void MoveDown() {
            mPos.y += mSpeed;
        }

        void SetY(int value) {
            mPos.y = value;
        }
        void Bounds(){
            if (GetY() < 0)
                SetY(0);
            if (GetY() + GetH() > SCREEN_HEIGHT)
                SetY(SCREEN_HEIGHT - GetH());
        }
        [[nodiscard]] bool Intersects( Pong::Net::Ball &ball) const;

        void Render(SDL2pp::Renderer &renderer, SDL2pp::Texture &board) {
            renderer.FillCopy(board, SDL2pp::NullOpt, mPos);

        }

        virtual void Move(const Ball& b) = 0;
        flatbuffers::Offset<Pong::Net::State::Player> Save(flatbuffers::FlatBufferBuilder &fbb);
        void Restore(const State::Player *player);
    private:
        SDL2pp::Rect mPos;
        int mSpeed{};
        int mScore{};



    }; // namespace Pong::Net
} // namespace Pong::Net