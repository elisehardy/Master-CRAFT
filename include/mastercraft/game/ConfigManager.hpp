#ifndef MASTERCRAFT_CONFIGMANAGER_HPP
#define MASTERCRAFT_CONFIGMANAGER_HPP

#include <string>

#include <GL/glew.h>

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
            static constexpr GLubyte GEN_MIN_HEIGHT = 128; /**< Minimum height when procedurally generating a chunk. */
            static constexpr GLubyte GEN_MAX_HEIGHT = 192; /**< Maximum height when procedurally generating a chunk. */
            static constexpr GLubyte GEN_CARVING_HEIGHT = GEN_MIN_HEIGHT + 30;
            static constexpr GLubyte GEN_INTERVAL_HEIGHT = GEN_MAX_HEIGHT - GEN_MIN_HEIGHT;
            static constexpr GLubyte GEN_WATER_LEVEL = GEN_MIN_HEIGHT + 22;
            
            static constexpr GLuint SECONDS_DAY_CYCLE = 60;
            static constexpr GLuint TICK_PER_SEC = 20;
            static constexpr GLuint TICK_CYCLE = SECONDS_DAY_CYCLE * TICK_PER_SEC;
            static constexpr GLuint TICK_DAY = static_cast<GLuint>(TICK_CYCLE * 0.5f);
            static constexpr GLuint TICK_NIGHT = TICK_DAY;
            
            static_assert(GEN_MIN_HEIGHT < GEN_MAX_HEIGHT);
        
        private:
            std::string OpenGLVersion; /**< Version of OpenGL. */
            std::string GLEWVersion;   /**< Version of GLEW. */
            std::string CPUInfo;       /**< CPU brand and core information. */
            
            GLfloat mouseSensitivity = 0.10f; /**< Sensitivity of the mouse, default to 0.5. */
            
            GLfloat fov = 70;          /**< Field of view, default to 70. */
            GLuint distanceView = 1;  /**< Draw distance as the radius of SuperChunk rendered. */
            GLuint framerate = 0;     /**< Framerate value, default to 0 (uncapped). */
            GLuint framerateInv = 0;  /**< Number of microseconds between frame. */
            Framerate framerateOpt = Framerate::FRAMERATE_UNCAPPED; /**< Chosen Framerate, default to uncapped. */
            
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
        
            [[nodiscard]] GLuint getDistanceView() const;
        
            void setDistanceView(GLuint distanceView);
        
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
    };
}

#endif //MASTERCRAFT_CONFIGMANAGER_HPP

