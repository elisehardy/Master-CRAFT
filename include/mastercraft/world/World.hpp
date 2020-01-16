#ifndef MASTERCRAFT_WORLD_HPP
#define MASTERCRAFT_WORLD_HPP

#include <memory>
#include <list>

#include <mastercraft/world/SuperChunk.hpp>
#include <mastercraft/shader/ShaderTexture.hpp>
#include <mastercraft/util/FreeflyCamera.hpp>
#include <mastercraft/util/SDLWindowManager.hpp>


namespace mastercraft::world {
    class World {
            std::list<std::shared_ptr<SuperChunk>> superchunks;
            util::SDLWindowManager window;
            shader::ShaderTexture cubeShader;
            util::FreeflyCamera camera;
    };
}

#endif
