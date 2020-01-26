#ifndef MASTERCRAFT_WINDOWMANAGER_HPP
#define MASTERCRAFT_WINDOWMANAGER_HPP

#include <SDL_video.h>
#include <SDL_events.h>

#include <mastercraft/util/ISingleton.hpp>


namespace mastercraft::game {
    
    class WindowManager : public util::INonCopyable {
        private:
            SDL_Window *window;
            SDL_GLContext context;
        
        public:
            
            explicit WindowManager(const char *title, uint32_t flags = SDL_WINDOW_OPENGL);
            
            ~WindowManager();
            
            void handleWindowEvent(const SDL_WindowEvent &event);
            
            void refresh();
            
            [[nodiscard]] SDL_DisplayMode getDisplayMode() const;
    };
}

#endif // MASTERCRAFT_WINDOWMANAGER_HPP
