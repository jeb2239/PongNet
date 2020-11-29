#pragma once
#include "SDL2pp/Renderer.hh"
#include "SDL2pp/SDL2pp.hh"
#include "Constants.hpp"
#include "Player.hpp"
#include "State_generated.h"
namespace Pong::Net
    {
        class Ball
        {
        public:
            Ball();


            void accelerate();
            void render(SDL2pp::Renderer &r,SDL2pp::Texture &tex);
            [[nodiscard]] const SDL2pp::Rect& GetRect() const; // do people return references?
            std::pair<bool, bool> Update(const Pong::Net::Player& p1, const Pong::Net::Player& p2);
            [[nodiscard]] int GetY() const {
                return mBall.GetY();
            }

            void Bounce(const Player &p1, const Player &p2);
            void Restore(const State::Ball*);
            flatbuffers::Offset<State::Ball> Save(flatbuffers::FlatBufferBuilder &fbb);
        private:
            float vx;
            float vy;
            float speed;
            SDL2pp::Rect mBall;



        };

    } // namespace Pong