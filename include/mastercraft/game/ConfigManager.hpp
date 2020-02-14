#ifndef MASTERCRAFT_CONFIGMANAGER_HPP
#define MASTERCRAFT_CONFIGMANAGER_HPP

#include <string>

#include <GL/glew.h>
#include <glm/vec3.hpp>

#include <mastercraft/util/INonCopyable.hpp>


namespace mastercraft::game {
    
    enum struct Framerate : GLbyte {
        FRAMERATE_60,
        FRAMERATE_75,
        FRAMERATE_120,
        FRAMERATE_144,
        FRAMERATE_180,
        FRAMERATE_240,
        FRAMERATE_VSYNC,
        FRAMERATE_UNCAPPED
    };
    
    
    
    class ConfigManager : public util::INonCopyable {
        public:
            
            // Terrain generation
            static constexpr GLubyte GEN_MIN_HEIGHT = 128; /**< Minimum height when procedurally generating a chunk. */
            static constexpr GLubyte GEN_MAX_HEIGHT = 192; /**< Maximum height when procedurally generating a chunk. */
            static constexpr GLubyte GEN_CARVING_HEIGHT = GEN_MIN_HEIGHT + 30;
            static constexpr GLubyte GEN_INTERVAL_HEIGHT = GEN_MAX_HEIGHT - GEN_MIN_HEIGHT;
            static constexpr GLubyte GEN_WATER_LEVEL = GEN_MIN_HEIGHT + 22;
            
            // Time
            static constexpr GLuint SECONDS_CYCLE = 40;
            static constexpr GLuint TICK_PER_SEC = 20;
            static constexpr GLuint TICK_CYCLE = SECONDS_CYCLE * TICK_PER_SEC;
            
            // Skybox and lighting
            static constexpr GLuint DAWN_START = game::ConfigManager::TICK_CYCLE / 360 * 350;
            static constexpr GLuint DAWN = game::ConfigManager::TICK_CYCLE / 360 * 360;
            static constexpr GLuint DAWN_END = game::ConfigManager::TICK_CYCLE / 360 * 30;
            
            static constexpr GLuint DUSK_START = game::ConfigManager::TICK_CYCLE / 360 * 170;
            static constexpr GLuint DUSK = game::ConfigManager::TICK_CYCLE / 360 * 190;
            static constexpr GLuint DUSK_END = game::ConfigManager::TICK_CYCLE / 360 * 210;
            
            static constexpr glm::vec3 DAWN_DUSK_SKYBOX_COLOR = glm::vec3(255.f, 188.f, 60.f) / 255.f;
            static constexpr glm::vec3 DAY_SKYBOX_COLOR = glm::vec3(42.f, 102.f, 175.f) / 255.f;
            static constexpr glm::vec3 NIGHT_SKYBOX_COLOR = glm::vec3(0.f, 0.f, 0.f) / 255.f;
            
            static constexpr glm::vec3 DAWN_DUSK_LIGHT_COLOR = glm::vec3(255.f, 60.f, 60.f) / 255.f;
            static constexpr glm::vec3 DAY_LIGHT_COLOR = glm::vec3(255.f, 255.f, 220.f) / 255.f;
            static constexpr glm::vec3 NIGHT_LIGHT_COLOR = glm::vec3(20.f, 60.f, 180.f) / 255.f;
            
            static constexpr GLfloat DAWN_DUSK_DIR_LIGHT_INTENSITY = .4f;
            static constexpr GLfloat DAY_LIGHT_DIR_INTENSITY = 1.f;
            static constexpr GLfloat NIGHT_LIGHT_DIR_INTENSITY = 0.f;
            
            static constexpr GLfloat DAWN_DUSK_AMB_LIGHT_INTENSITY = .3f;
            static constexpr GLfloat DAY_LIGHT_AMB_INTENSITY = .4f;
            static constexpr GLfloat NIGHT_LIGHT_AMB_INTENSITY = .15f;
            
            static_assert(GEN_MIN_HEIGHT < GEN_MAX_HEIGHT);
        
        private:
            std::string OpenGLVersion; /**< Version of OpenGL. */
            std::string GLEWVersion;   /**< Version of GLEW. */
            std::string CPUInfo;       /**< CPU brand and core information. */
            
            GLfloat mouseSensitivity = 0.10f; /**< Sensitivity of the mouse, default to 0.5. */
            
            GLfloat fov = 70;         /**< Field of view, default to 70. */
            GLint distanceView = 6;   /**< Draw distance as the radius of SuperChunk rendered. */
            GLuint framerate = 0;     /**< Framerate value, default to 0 (uncapped). */
            GLuint usPerFrame = 0;    /**< Number of microseconds between frame. */
            Framerate framerateOpt = Framerate::FRAMERATE_VSYNC;  /**< Chosen Framerate, default to VSYNC. */
            
            GLboolean faceCulling = true;      /**< Whether face culling is enabled. */
            GLboolean occlusionCulling = true; /**< Whether occlusion culling is enabled. */
            GLboolean frustumCulling = true;   /**< Whether frustum culling is enabled. */
            GLboolean debug = false;           /**< Whether debug display. */
        
        public:
            
            ConfigManager() = default;
            
            void init();
            
            [[nodiscard]] std::string getOpenGlVersion() const;
            
            void setOpenGlVersion(const std::string &openGlVersion);
            
            [[nodiscard]] std::string getGlewVersion() const;
            
            void setGlewVersion(const std::string &GlewVersion);
            
            [[nodiscard]] std::string getCpuInfo() const;
            
            void setCpuInfo(const std::string &cpuinfo);
            
            [[nodiscard]] GLfloat getMouseSensitivity() const;
            
            void setMouseSensitivity(GLfloat mouseSensitivity);
            
            [[nodiscard]] GLuint getFramerate() const;
            
            [[nodiscard]] GLuint getFramerateInv() const;
            
            [[nodiscard]] std::string getFramerateString() const;
            
            void setFramerate(Framerate framerate);
            
            void cycleFramerate();
            
            [[nodiscard]] GLfloat getFov() const;
            
            void setFov(GLfloat fov);
            
            [[nodiscard]] GLint getDistanceView() const;
            
            void setDistanceView(GLint distanceView);
            
            void incDistanceView();
            
            void decDistanceView();
            
            [[nodiscard]] GLboolean getFaceCulling() const;
            
            void setFaceCulling(GLboolean faceCulling);
            
            void switchFaceCulling();
            
            [[nodiscard]] GLboolean getOcclusionCulling() const;
            
            void setOcclusionCulling(GLboolean occlusionCulling);
            
            void switchOcclusionCulling();
            
            [[nodiscard]] GLboolean getFrustumCulling() const;
            
            void setFrustumCulling(GLboolean frustumCulling);
            
            void switchFrustumCulling();
            
            [[nodiscard]] GLboolean getDebug() const;
            
            void setDebug(GLboolean debug);
            
            void switchDebug();
        
            [[nodiscard]] static GLfloat changeIntervalTo01(GLfloat x, GLfloat oldMin, GLfloat oldMax);
        
            [[nodiscard]] static glm::vec3 getSkyboxColor(GLuint tick);
            
            [[nodiscard]] static glm::vec3 getLightColor(GLuint tick);
            
            [[nodiscard]] static GLfloat getLightDirIntensity(GLuint tick);
            
            [[nodiscard]] static GLfloat getLightAmbIntensity(GLuint tick);
    };
}

#endif //MASTERCRAFT_CONFIGMANAGER_HPP

