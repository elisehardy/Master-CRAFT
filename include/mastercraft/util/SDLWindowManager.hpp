#pragma once

#include <cstdint>

#include <SDL2/SDL.h>
#include <glimac/glm.hpp>


namespace mastercraft::util {
    
    class SDLWindowManager {
        private:
            SDL_Window *window;
            SDL_GLContext context;
            
        public:
            explicit SDLWindowManager(const char *title);
            
            ~SDLWindowManager();
        
            void refresh();
        
            bool pollEvent(SDL_Event &e);
            
            [[nodiscard]] int getWidth() const;
        
            [[nodiscard]] int getHeight() const;
            
            [[nodiscard]] bool isKeyPressed(SDL_Scancode key) const;
        
            [[nodiscard]] bool isMouseButtonPressed(uint32_t button) const;
            
            [[nodiscard]] glm::ivec2 getMousePosition() const;
    };
    
}
