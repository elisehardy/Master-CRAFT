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
#include <mastercraft/entity/Sun.hpp>


namespace mastercraft::game {
    
    /**
     * ISingleton representing the whole game, it store the game's States and main constants.
     */
    class Game : public util::ISingleton {
        private:
            
            Game();
        
        public:
            std::chrono::steady_clock::time_point lastTick;
            std::unique_ptr<WindowManager> windowManager;
            std::unique_ptr<ConfigManager> configManager;
            std::unique_ptr<InputManager> inputManager;
            std::unique_ptr<ChunkManager> chunkManager;
            std::unique_ptr<entity::Sun> sun;
            std::unique_ptr<Camera> camera;
            GLboolean running; /**< Boolean indicating if the game is running or should cleaned up and quit. */
            
            
            /**
             * Delete move constructor.
             */
            Game(Game &&) = delete;
            
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
             * 'ConfigManager::tickRate' ticks per second.
             *
             * @return true if a tick happened.
             */
            bool tick();
            
            /**
             * Update the game.
             *
             * @param event An instance of Event containing the inputs of the user.
             */
            void update();
            
            /**
             * Draw the State at the top of the stack.
             */
            void render();
            
            /**
             * Stops the game.
             *
             * @return true
             */
            void stop();
            
            /**
             * Return whether the game is currently running or should be cleaned-up and closes.
             */
            [[nodiscard]] bool isRunning();
    };
}

#endif // ENGINE_HPP
