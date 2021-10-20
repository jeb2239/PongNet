#include "Game.hpp"
#include "Constants.hpp"
#include "SDL2pp/Optional.hh"
#include "SDL2pp/Rect.hh"
#include "SDL2pp/Renderer.hh"
#include "SDL2pp/Texture.hh"
#include "SDL2pp/Window.hh"
#include "SDL_events.h"
#include "SDL_render.h"
#include <SDL_video.h>
#include "Player.hpp"
#include <memory>
#include <fstream>
#include "gflags/gflags.h"
#include "glog/logging.h"


#include "SDL2pp/Rect.hh"
namespace Pong::Net {

// find a better soln



    Game::Game(moodycamel::BlockingReaderWriterQueue<DataPacket>& r) : rwq(r),mWindow("Pong::Net",
                           SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                           SCREEN_WIDTH, SCREEN_HEIGHT,
                           SDL_WINDOW_SHOWN),
                   mRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
                   mBoardTexture(mRenderer, DATA_PATH "/pong_board.png"),
                   p1(mBoardTexture.GetWidth() / 2 + 10, SCREEN_HEIGHT / 2 - 150 / 2,
                      mBoardTexture.GetWidth(), 150, 10),
                   p2(SCREEN_WIDTH - mBoardTexture.GetWidth() / 2 - 10 - mBoardTexture.GetWidth() / 2,
                      SCREEN_HEIGHT / 2 - 150 / 2,
                      mBoardTexture.GetWidth(), 150, 10)  {


    }

    void Game::run() {
        mRunning = true;
        while (mRunning) { //FPS calculator
            uint prevTime = SDL_GetTicks();
            ++frames;
            uint currTime = SDL_GetTicks();
            uint elapsed = currTime - prevTime;

            if (elapsed > 100) {
                fps = (int) std::round(frames / (elapsed / 1000.0));
                frames = 0;
            }
            processEvents();
            // pushFullGameState();
        }
    }

    void Game::update() {
        //move player button press
        //
        p1.Move(mBall);
        // Basic AI
        p2.Move(mBall);

        std::pair<bool,bool> scores = mBall.Update(p1, p2);
        if (scores.first) {
            p1.Scored();
        }
        if (scores.second) {
            p2.Scored();
        }
        /*
        list | process | events | 
        sound events

        render - processevent+ai+buttons -  (update apply changes moves w/o consequences)  - (phys collide) - 
        */
        mBall.Update(p1, p2);
        mBall.Bounce(p1, p2);
        p1.Bounds();
        p2.Bounds();
        // push whole world
        

    }

    void Game::render() {
        mRenderer.Clear();
        p1.Render(mRenderer, mBoardTexture);
        p2.Render(mRenderer, mBoardTexture);
        //this will be refractored to the ball class
        renderTexture(mBoardTexture, mRenderer, SCREEN_WIDTH / 2 - CENTER_WIDTH / 2, 0, CENTER_WIDTH,
                      SCREEN_HEIGHT);
        mBall.render(mRenderer, mBoardTexture);
        mRenderer.Present();
    }

    void Game::processEvents() {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
           render(); // can take a long time 
            // process messages, stuff user thought of 
            switch (event.type) {
                case SDL_QUIT:
                    LOG(INFO) << "Shutting Down";
                    mRunning = false;
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym==SDLK_a){
                        stateSave();
                        LOG(INFO) << "Saving ...";
                    }
                    if(event.key.keysym.sym==SDLK_d){
                        pushFullGameState();
                    }
                    break;
                default:
                    break;
            }
        }

        //move
        update(); // apply what ever happend in event handler

         /*maybe sleep at end
         might be broken out, 
         use lists, 
         collision, 
         lists
        */


       
    }

    void Game::stateSave() {
        flatbuffers::FlatBufferBuilder fbb;
        auto p1Offset=p1.Save(fbb);
        auto p2Offset=p2.Save(fbb);
        auto ballOffset=mBall.Save(fbb);
        auto game = State::CreateGame(fbb, p1Offset,p2Offset,ballOffset);
        State::FinishGameBuffer(fbb, game);
        uint8_t *buf = fbb.GetBufferPointer();
        std::ofstream ofs("GameState.bin", std::ios::binary);
        ofs.write((char *) buf, fbb.GetSize());

    }
    
    void Game::pushFullGameState(){
        flatbuffers::FlatBufferBuilder fbb;
        auto p1Offset=p1.Save(fbb);
        auto p2Offset=p2.Save(fbb);
        auto ballOffset=mBall.Save(fbb);
        auto game = State::CreateGame(fbb, p1Offset,p2Offset,ballOffset);
        int oppId=0;
        
        auto message = State::CreateMessage(fbb,oppId,Pong::Net::State::PacketType_ReplicationData,game.Union());
        fbb.FinishSizePrefixed(message);
        
        rwq.enqueue(fbb.GetBufferSpan());
        
        // this fbb is never touched again by this thread
        
        
        
    }

    void Game::loadSaveState(const std::string& s) {

        std::ifstream infile;
        infile.open(s, std::ios::binary | std::ios::in);
        infile.seekg(0,std::ios::end);
        int length = infile.tellg();
        infile.seekg(0,std::ios::beg);
        char *data = new char[length];
        infile.read(data, length);
        infile.close();



    }

} // namespace Pong::Net
