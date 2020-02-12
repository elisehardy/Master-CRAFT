#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <stack>
#include <cstdint>
#include <chrono>

#include <mastercraft/util/ISingleton.hpp>
#include <mastercraft/game/ConfigManager.hpp>
#include <mastercraft/game/Camera.hpp>
#include <mastercraft/game/InputManager.hpp>
#include <mastercraft/game/WindowManager.hpp>
#include <mastercraft/game/ChunkManager.hpp>
#include <mastercraft/game/Debug.hpp>
#include <mastercraft/game/Statistics.hpp>
#include <mastercraft/entity/Skybox.hpp>
#include <mastercraft/entity/Sun.hpp>


namespace mastercraft::game {
    
    /**
     * ISingleton representing the whole game, it store the game's States and main constants.
     */
    class Game : public util::ISingleton {
        private:
            
            Game();
        
        public:
            std::unique_ptr<WindowManager> windowManager;
            std::unique_ptr<ConfigManager> configManager;
            std::unique_ptr<InputManager> inputManager;
            std::unique_ptr<ChunkManager> chunkManager;
            std::unique_ptr<entity::Skybox> skybox;
            std::unique_ptr<entity::Sun> sun;
            std::unique_ptr<Camera> camera;
            std::unique_ptr<Debug> debug;
            Statistics stats;
            
            std::chrono::steady_clock::time_point lastTick;
            GLuint tickSecond;
            GLuint tickDay;
            GLboolean running; /**< Boolean indicating if the game is running or should cleaned up and quit. */
            
            
            /**
             * Return the instance of Game.
             *
             * @return The instance of Game.
             */
            static Game *getInstance();
            
            /**
             * Initialize the game.
             */
            void init();
            
            /**
             * Cleanup the whole game.
             */
            void cleanup();
            
            /**
             * Check whether the game should be updated, so that the game loop runs at a fixed rate of
             * 'ConfigManager::TICK_PER_SEC' ticks per second.
             *
             * @return true if a tick happened.
             */
            bool tick();
            
            /**
             * Update the game.
             */
            void update();
            
            /**
             * Draw the State at the top of the stack.
             */
            void render();
            
            /**
             * Stops the game.
             */
            void stop();
            /**
             * Return whether the game is currently running or should be cleaned-up and closes.
             */
            [[nodiscard]] bool isRunning();
    };
}

#endif // ENGINE_HPP
