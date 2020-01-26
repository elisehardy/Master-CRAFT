#ifndef MASTERCRAFT_CONFIGMANAGER_HPP
#define MASTERCRAFT_CONFIGMANAGER_HPP

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
        private:
            const GLubyte *OpenGLVersion = nullptr; /**< Version of OpenGL. */
            const GLubyte *GLEWVersion = nullptr;   /**< Version of GLEW. */
            
            GLfloat mouseSensitivity = 0.10; /**< Sensitivity of the mouse, default to 0.5. */
            
            GLfloat fov = 70;          /**< Field of view, default to 70. */
            GLubyte drawDistance = 1;  /**< Draw distance as the radius of SuperChunk rendered. */
            GLubyte framerate = 0;     /**< Framerate real value, default to 0 (uncapped). */
            Framerate framerateOpt = Framerate::FRAMERATE_UNCAPPED; /**< Chosen Framerate, default to uncapped. */
            
            GLboolean faceCulling = true;      /**< Whether face culling is enabled. */
            GLboolean occlusionCulling = true; /**< Whether occlusion culling is enabled. */
            GLboolean frustumCulling = true;   /**< Whether frustum culling is enabled. */
            GLboolean debug = false;           /**< Whether debug display. */
        
        public:
            
            ConfigManager() = default;
            
            [[nodiscard]] const GLubyte *getOpenGlVersion() const;
            
            void setOpenGlVersion(const GLubyte *openGlVersion);
            
            [[nodiscard]] const GLubyte *getGlewVersion() const;
            
            void setGlewVersion(const GLubyte *glewVersion);
        
            [[nodiscard]] GLfloat getMouseSensitivity() const;
            
            void setMouseSensitivity(GLfloat mouseSensitivity);
            
            [[nodiscard]] GLubyte getFramerate() const;
            
            void setFramerate(Framerate framerate);
            
            [[nodiscard]] GLfloat getFov() const;
            
            void setFov(GLfloat fov);
            
            [[nodiscard]] GLubyte getDrawDistance() const;
            
            void setDrawDistance(GLubyte drawDistance);
            
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

