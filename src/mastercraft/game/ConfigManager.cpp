#include <sstream>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <cpuid/libcpuid.h>

#include <mastercraft/game/ConfigManager.hpp>
#include <mastercraft/game/Game.hpp>


namespace mastercraft::game {
    
    void ConfigManager::init() {
        this->setOpenGlVersion(reinterpret_cast<const char *>(glGetString(GL_VERSION)));
        this->setGlewVersion(reinterpret_cast<const char *>(glewGetString(GLEW_VERSION)));
        this->setFaceCulling(true);
        SDL_SetRelativeMouseMode(SDL_TRUE);
        
        struct cpu_raw_data_t raw {};
        struct cpu_id_t data {};
        if (cpuid_get_raw_data(&raw) < 0) {
            this->CPUInfo = "Unknown";
        }
        else if (cpu_identify(&raw, &data) < 0) {
            this->CPUInfo = "Unknown";
        }
        else {
            std::stringstream ss;
            ss << data.brand_str << " - " << data.num_cores << " cores (" << data.num_logical_cpus << " threads)";
            this->CPUInfo = ss.str();
        }
    }
    
    
    std::string ConfigManager::getOpenGlVersion() const {
        return this->OpenGLVersion;
    }
    
    
    void ConfigManager::setOpenGlVersion(const std::string &openGlVersion) {
        this->OpenGLVersion = openGlVersion;
    }
    
    
    std::string ConfigManager::getGlewVersion() const {
        return this->GLEWVersion;
    }
    
    
    void ConfigManager::setGlewVersion(const std::string &glewVersion) {
        this->GLEWVersion = glewVersion;
    }
    
    
    std::string ConfigManager::getCpuInfo() const {
        return this->CPUInfo;
    }
    
    
    void ConfigManager::setCpuInfo(const std::string &cpuInfo) {
        this->CPUInfo = cpuInfo;
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
    
    
    std::string ConfigManager::getFramerateString() const {
        switch (this->framerateOpt) {
            case Framerate::FRAMERATE_60:
                return "80";
            case Framerate::FRAMERATE_75:
                return "70";
            case Framerate::FRAMERATE_120:
                return "120";
            case Framerate::FRAMERATE_144:
                return "144";
            case Framerate::FRAMERATE_180:
                return "180";
            case Framerate::FRAMERATE_240:
                return "240";
            case Framerate::FRAMERATE_VSYNC:
                return std::to_string(this->framerate) + " (VSYNC)";
            case Framerate::FRAMERATE_UNCAPPED:
                return "Uncapped";
        }
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
                this->framerate = static_cast<GLubyte>(
                    Game::getInstance()->windowManager->getDisplayMode().refresh_rate
                );
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
    
    
    GLuint ConfigManager::getDistanceView() const {
        return distanceView;
    }
    
    
    void ConfigManager::setDistanceView(GLuint distanceView) {
        this->distanceView = distanceView;
    }
    
    
    GLboolean ConfigManager::getFaceCulling() const {
        return faceCulling;
    }
    
    
    void ConfigManager::setFaceCulling(GLboolean faceCulling) {
        this->faceCulling = faceCulling;
    }
    
    
    void ConfigManager::switchFaceCulling() {
        this->faceCulling = !this->faceCulling;
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
