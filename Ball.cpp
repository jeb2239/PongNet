#include "Ball.hpp"
#include "Constants.hpp"
#include "Player.hpp"
#include "State_generated.h"

namespace Pong::Net {
    Ball::Ball() :
            vx((rand() % 2 == 0) ? BALL_INIT_SPEED : -1 * BALL_INIT_SPEED),
            vy(-0.5f),
            speed(BALL_INIT_SPEED),
            mBall((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), BALL_HEIGHT, BALL_HEIGHT) {
    }

    void Ball::render(SDL2pp::Renderer &r, SDL2pp::Texture &tex) {
        r.DrawRect(mBall);
        renderTexture(tex, r, mBall.x, mBall.y, BALL_WIDTH, BALL_HEIGHT);
    }

    std::pair<bool, bool> Ball::Update(const Player &p1, const Player &p2) {

        if (vx > BALL_MAXSPEED)
            vx = BALL_MAXSPEED;

        if (vy > BALL_MAXSPEED)
            vy = BALL_MAXSPEED;

        // Ball Coords
        // Update Ball coordinates
        mBall.x += (int) vx;
        mBall.y += (int) vy;

        // Boundary Collision for Bottom and top of screen
        if (mBall.y < 0) {
            mBall.y = 0;
            vy *= -1;
        }

        if (mBall.y + BALL_HEIGHT >= SCREEN_HEIGHT) {
            mBall.y = SCREEN_HEIGHT - BALL_HEIGHT - 1;
            vy *= -1;
        }
        bool p1_scored = false;
        bool p2_scored = false;
        //score on P1
        if (mBall.x < 0) {

            p2_scored = true;
            mBall.x = p1.GetX() + p1.GetW();
            mBall.y = p1.GetY() + p1.GetH() / 2;
            vx = BALL_INIT_SPEED;
            speed = BALL_INIT_SPEED;
        }
        //score on P2
        if (mBall.x + BALL_WIDTH >= SCREEN_WIDTH) {

            p1_scored = true;
            mBall.x = p2.GetX() - BALL_WIDTH;
            mBall.y = p2.GetY() + p2.GetH() / 2;
            vx = -1 * BALL_INIT_SPEED;
            speed = BALL_INIT_SPEED;
        }

        return std::make_pair(p1_scored, p2_scored);
    }

    void Ball::Bounce(const Player &p1, const Player &p2) {
        if (p1.Intersects(*this)) {
            mBall.x = p1.GetX() + p1.GetW();

            speed = speed * BALL_ACCELERATE;

            float angle = calc_angle(p1.GetY(), mBall.y, p1.GetH());
            vx = speed * cos(angle);
            vy = ((vy > 0) ? -1 : 1) * speed * sin(angle);
        }
        //refactor into bounce methods
        if (p2.Intersects(*this)) {
            mBall.x = p2.GetX() - BALL_WIDTH;

            accelerate();

            float angle = calc_angle(p2.GetY(), mBall.y, p2.GetH());
            vx = -1 * speed * cos(angle);
            vy = ((vy > 0) ? -1 : 1) * speed * sin(angle);
        }

    }

    const SDL2pp::Rect &Ball::GetRect() const {

        return mBall;
    }

    void Ball::accelerate() {
        speed *= BALL_ACCELERATE;
    }

    flatbuffers::Offset<State::Ball> Ball::Save(flatbuffers::FlatBufferBuilder& fbb) {
        State::Rect rect(mBall.x, mBall.y, mBall.w, mBall.h);
        return State::CreateBall(fbb, vx, vy, speed, &rect);

    }

    void Ball::Restore(const State::Ball * b) {
        RestoreRect(mBall,b->rect());
        this->speed=b->speed();
        this->vx=b->vx();
        this->vy=b->vy();

    }


} // namespace Pong::Net