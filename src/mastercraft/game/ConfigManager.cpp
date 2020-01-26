#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <mastercraft/game/ConfigManager.hpp>
#include <mastercraft/game/Game.hpp>


namespace mastercraft::game {
    
    const GLubyte *ConfigManager::getOpenGlVersion() const {
        return OpenGLVersion;
    }
    
    
    void ConfigManager::setOpenGlVersion(const GLubyte *openGlVersion) {
        OpenGLVersion = openGlVersion;
    }
    
    
    const GLubyte *ConfigManager::getGlewVersion() const {
        return GLEWVersion;
    }
    
    
    void ConfigManager::setGlewVersion(const GLubyte *glewVersion) {
        GLEWVersion = glewVersion;
    }
    
    
    GLfloat ConfigManager::getMouseSensitivity() const {
        return mouseSensitivity;
    }
    
    
    void ConfigManager::setMouseSensitivity(GLfloat mouseSensitivity) {
        this->mouseSensitivity = mouseSensitivity;
    }
    
    
    GLubyte ConfigManager::getFramerate() const {
        return framerate;
    }
    
    
    void ConfigManager::setFramerate(Framerate framerate) {
        this->framerateOpt = framerate;
        
        switch (framerate) {
            case Framerate::FRAMERATE_60:
                this->framerate = 60;
                break;
            case Framerate::FRAMERATE_75:
                this->framerate = 75;
                break;
            case Framerate::FRAMERATE_120:
                this->framerate = 120;
                break;
            case Framerate::FRAMERATE_144:
                this->framerate = 144;
                break;
            case Framerate::FRAMERATE_180:
                this->framerate = 180;
                break;
            case Framerate::FRAMERATE_240:
                this->framerate = 240;
                break;
            case Framerate::FRAMERATE_VSYNC:
                this->framerate = Game::getInstance()->windowManager->getDisplayMode().refresh_rate;
                this->framerate = this->framerate ? this->framerate : 60;
                break;
            case Framerate::FRAMERATE_UNCAPPED:
                this->framerate = 0;
                break;
        }
    }
    
    
    GLfloat ConfigManager::getFov() const {
        return fov;
    }
    
    
    void ConfigManager::setFov(GLfloat fov) {
        this->fov = fov;
        Game *game = Game::getInstance();
        SDL_DisplayMode display = game->windowManager->getDisplayMode();
        game->camera->setProjectionMatrix(fov, display.w, display.h);
    }
    
    
    GLubyte ConfigManager::getDrawDistance() const {
        return drawDistance;
    }
    
    
    void ConfigManager::setDrawDistance(GLubyte drawDistance) {
        this->drawDistance = drawDistance;
    }
    
    
    GLboolean ConfigManager::getFaceCulling() const {
        return faceCulling;
    }
    
    
    void ConfigManager::setFaceCulling(GLboolean faceCulling) {
        this->faceCulling = faceCulling;
        if (faceCulling) {
            glEnable(GL_CULL_FACE);
        }
        else {
            glDisable(GL_CULL_FACE);
        }
    }
    
    
    void ConfigManager::switchFaceCulling() {
        this->faceCulling = !this->faceCulling;
        if (this->faceCulling) {
            glEnable(GL_CULL_FACE);
        }
        else {
            glDisable(GL_CULL_FACE);
        }
    }
    
    
    GLboolean ConfigManager::getOcclusionCulling() const {
        return occlusionCulling;
    }
    
    
    void ConfigManager::setOcclusionCulling(GLboolean occlusionCulling) {
        this->occlusionCulling = occlusionCulling;
    }
    
    
    void ConfigManager::switchOcclusionCulling() {
        this->occlusionCulling = !this->occlusionCulling;
    }
    
    
    GLboolean ConfigManager::getFrustumCulling() const {
        return frustumCulling;
    }
    
    
    void ConfigManager::setFrustumCulling(GLboolean frustumCulling) {
        this->frustumCulling = frustumCulling;
    }
    
    
    void ConfigManager::switchFrustumCulling() {
        this->frustumCulling = !this->frustumCulling;
    }
    
    
    GLboolean ConfigManager::getDebug() const {
        return debug;
    }
    
    
    void ConfigManager::setDebug(GLboolean debug) {
        this->debug = debug;
    }
    
    
    void ConfigManager::switchDebug() {
        this->debug = !this->debug;
    }
}
