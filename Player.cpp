#include "Player.hpp"
#include "Ball.hpp"


bool Pong::Net::Player::Intersects(Pong::Net::Ball &ball)  const {
    return mPos.Intersects(ball.GetRect());
}

 flatbuffers::Offset<Pong::Net::State::Player> Pong::Net::Player::Save(flatbuffers::FlatBufferBuilder& fbb) {
        State::Rect pos(mPos.x,mPos.y,mPos.w,mPos.h);
        return State::CreatePlayer(fbb,&pos,mSpeed,mScore);


}

void Pong::Net::Player::Restore(const Pong::Net::State::Player *player) {
    RestoreRect(mPos,player->pos());
    this->mScore=player->score();
    this->mSpeed=player->speed();

}



