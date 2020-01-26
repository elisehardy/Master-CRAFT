#ifndef MASTERCRAFT_INPUTMANAGER_HPP
#define MASTERCRAFT_INPUTMANAGER_HPP

#include <SDL_events.h>

#include <mastercraft/util/INonCopyable.hpp>


namespace mastercraft::game {
    
    class InputManager: public util::INonCopyable {
        private:
            bool isKeyPressed(SDL_Scancode key);
            
        public:
            
            InputManager();
            
            void handleMouseMotion(const SDL_MouseMotionEvent &event);
            
            void handleMouseButton(const SDL_MouseButtonEvent &event);
            
            void handleMouseWheel(const SDL_MouseWheelEvent &event);
            
            void handleKeyboard(const SDL_KeyboardEvent &event);
            
            void handleHeldMouseButton();
            
            void handleHeldKey();
    };
}

#endif //MASTERCRAFT_INPUTMANAGER_HPP
