#pragma once
#include <concepts>
namespace Pong::Net {
    template<typename ItemToRender>
    concept SDLRenderable = requires (ItemToRender itr,SDL2pp::Renderer& r){
        itr.render(r);
    };

}