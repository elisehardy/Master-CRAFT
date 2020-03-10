#include <sstream>
#include <iostream>

#include <cpuid/libcpuid.h>

#include <mastercraft/game/ConfigManager.hpp>
#include <mastercraft/game/Game.hpp>


namespace mastercraft::game {
    
    void ConfigManager::init() {
        this->setOpenGlVersion(reinterpret_cast<const char *>(glGetString(GL_VERSION)));
        this->setGlewVersion(reinterpret_cast<const char *>(glewGetString(GLEW_VERSION)));
        this->setFaceCulling(true);
        this->setFramerate(Framerate::FRAMERATE_VSYNC);
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
    
    
    GLuint ConfigManager::getFramerate() const {
        return framerate;
    }
    
    
    GLuint ConfigManager::getFramerateInv() const {
        return usPerFrame;
    }
    
    
    std::string ConfigManager::getFramerateString() const {
        switch (this->framerateOpt) {
            case Framerate::FRAMERATE_60:
                return "60";
            case Framerate::FRAMERATE_75:
                return "75";
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
        GLuint fps;
        
        this->framerateOpt = framerate;
        
        switch (framerate) {
            case Framerate::FRAMERATE_60:
                this->framerate = 60;
                this->usPerFrame = static_cast<GLuint>(1. / 60. * 1e6);
                break;
            case Framerate::FRAMERATE_75:
                this->framerate = 75;
                this->usPerFrame = static_cast<GLuint>(1. / 75. * 1e6);
                break;
            case Framerate::FRAMERATE_120:
                this->framerate = 120;
                this->usPerFrame = static_cast<GLuint>(1. / 120. * 1e6);
                break;
            case Framerate::FRAMERATE_144:
                this->framerate = 144;
                this->usPerFrame = static_cast<GLuint>(1. / 144. * 1e6);
                break;
            case Framerate::FRAMERATE_180:
                this->framerate = 180;
                this->usPerFrame = static_cast<GLuint>(1. / 180. * 1e6);
                break;
            case Framerate::FRAMERATE_240:
                this->framerate = 240;
                this->usPerFrame = static_cast<GLuint>(1. / 240. * 1e6);
                break;
            case Framerate::FRAMERATE_VSYNC:
                fps = static_cast<GLuint>(Game::getInstance()->windowManager->getDisplayMode().refresh_rate);
                this->framerate = fps ? fps : 60;
                this->usPerFrame = static_cast<GLuint>(1. / this->framerate * 1e6);
                break;
            case Framerate::FRAMERATE_UNCAPPED:
                this->framerate = 0;
                this->usPerFrame = 0;
                break;
        }
    }
    
    
    void ConfigManager::cycleFramerate() {
        switch (this->framerateOpt) {
            case Framerate::FRAMERATE_60:
                this->setFramerate(Framerate::FRAMERATE_75);
                break;
            case Framerate::FRAMERATE_75:
                this->setFramerate(Framerate::FRAMERATE_120);
                break;
            case Framerate::FRAMERATE_120:
                this->setFramerate(Framerate::FRAMERATE_144);
                break;
            case Framerate::FRAMERATE_144:
                this->setFramerate(Framerate::FRAMERATE_180);
                break;
            case Framerate::FRAMERATE_180:
                this->setFramerate(Framerate::FRAMERATE_240);
                break;
            case Framerate::FRAMERATE_240:
                this->setFramerate(Framerate::FRAMERATE_VSYNC);
                break;
            case Framerate::FRAMERATE_VSYNC:
                this->setFramerate(Framerate::FRAMERATE_UNCAPPED);
                break;
            case Framerate::FRAMERATE_UNCAPPED:
                this->setFramerate(Framerate::FRAMERATE_60);
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
    
    
    GLint ConfigManager::getDistanceView() const {
        return distanceView;
    }
    
    
    void ConfigManager::setDistanceView(GLint distanceView) {
        this->distanceView = distanceView;
    }
    
    
    void ConfigManager::incDistanceView() {
        this->distanceView = std::min(this->distanceView + 1, 32);
    }
    
    
    void ConfigManager::decDistanceView() {
        this->distanceView = std::max(this->distanceView - 1, 0);
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
    GLboolean ConfigManager::getScore() const {
        return score;
    }
    
    void ConfigManager::setDebug(GLboolean debug) {
        this->debug = debug;
    }

    void ConfigManager::switchScore() {
        this->score = !this->score;
    }
    
    void ConfigManager::switchDebug() {
        this->debug = !this->debug;
    }
    
    
    GLfloat ConfigManager::changeIntervalTo01(GLfloat x, GLfloat oldMin, GLfloat oldMax) {
        GLfloat oldRange = (oldMax - oldMin);
        GLfloat newRange = (1.f - 0.f);
        
        return std::min(1.f, std::max(0.f, (((x - oldMin) * newRange) / oldRange)));
    }
    
    
    #pragma clang diagnostic push
    #pragma ide diagnostic ignored "OCSimplifyInspection"
    #pragma ide diagnostic ignored "bugprone-branch-clone"
    #pragma ide diagnostic ignored "misc-redundant-expression"
    
    
    glm::vec3 ConfigManager::getSkyboxColor(GLint tick) {
        GLfloat value;
    
        // Day
        if (DUSK_START - DAWN_END < 0 && ((tick >= DAWN_END && tick <= TICK_CYCLE) || tick <= DUSK_START)) {
            return DAY_SKYBOX_COLOR;
        }
        if (tick >= DAWN_END && tick <= DUSK_START) {
            return DAY_SKYBOX_COLOR;
        }
    
        // Night
        if (DAWN_START - DUSK_END < 0 && ((tick >= DUSK_END && tick <= TICK_CYCLE) || tick <= DAWN_START)) {
            return NIGHT_SKYBOX_COLOR;
        }
        if (tick >= DUSK_END && tick <= DAWN_START) {
            return NIGHT_SKYBOX_COLOR;
        }
    
        // Day to Dusk
        if (DUSK - DUSK_START < 0 && ((tick >= DUSK_START && tick <= TICK_CYCLE) || tick <= DUSK)) {
            if (tick > 0 && 0 < DUSK) {
                tick += TICK_CYCLE;
            }
        
            value = changeIntervalTo01(tick, DAWN_START, DUSK + TICK_CYCLE);
            return glm::mix(DAY_SKYBOX_COLOR, DAWN_DUSK_SKYBOX_COLOR, value);
        }
        if (tick >= DUSK_START && tick <= DUSK) {
            value = changeIntervalTo01(tick, DUSK_START, DUSK);
            return glm::mix(DAY_SKYBOX_COLOR, DAWN_DUSK_SKYBOX_COLOR, value);
        }
    
        // Dusk to Night
        if (DUSK_END - DUSK < 0 && ((tick >= DUSK && tick <= TICK_CYCLE) || tick <= DUSK_END)) {
            if (tick > 0 && 0 < DUSK_END) {
                tick += TICK_CYCLE;
            }
        
            value = changeIntervalTo01(tick, DAWN_START, DUSK_END + TICK_CYCLE);
            return glm::mix(DAWN_DUSK_SKYBOX_COLOR, NIGHT_SKYBOX_COLOR, value);
        }
        if (tick >= DUSK && tick <= DUSK_END) {
            value = changeIntervalTo01(tick, DUSK, DUSK_END);
            return glm::mix(DAWN_DUSK_SKYBOX_COLOR, NIGHT_SKYBOX_COLOR, value);
        }
    
        // Night to Dawn
        if (DAWN - DAWN_START < 0 && ((tick >= DAWN_START && tick <= TICK_CYCLE) || tick <= DAWN)) {
            if (tick > 0 && 0 < DAWN) {
                tick += TICK_CYCLE;
            }
        
            value = changeIntervalTo01(tick, DAWN_START, DAWN + TICK_CYCLE);
            return glm::mix(NIGHT_SKYBOX_COLOR, DAWN_DUSK_SKYBOX_COLOR, value);
        }
        if (tick >= DAWN_START && tick <= DAWN) {
            value = changeIntervalTo01(tick, DAWN_START, DAWN);
            return glm::mix(NIGHT_SKYBOX_COLOR, DAWN_DUSK_SKYBOX_COLOR, value);
        }
    
        // Dawn to Day
        if (DAWN_END - DAWN < 0 && ((tick >= DAWN && tick <= TICK_CYCLE) || tick <= DAWN_END)) {
            if (tick > 0 && 0 < DAWN_END) {
                tick += TICK_CYCLE;
            }
        
            value = changeIntervalTo01(tick, DAWN, DAWN_END + TICK_CYCLE);
            return glm::mix(DAWN_DUSK_SKYBOX_COLOR, DAY_SKYBOX_COLOR, value);
        }
        else {
            value = changeIntervalTo01(tick, DAWN, DAWN_END);
            return glm::mix(DAWN_DUSK_SKYBOX_COLOR, DAY_SKYBOX_COLOR, value);
        }
    }
    
    
    glm::vec3 ConfigManager::getLightColor(GLint tick) {
        GLfloat value;
    
        // Day
        if (DUSK_START - DAWN_END < 0 && ((tick >= DAWN_END && tick <= TICK_CYCLE) || tick <= DUSK_START)) {
            return DAY_LIGHT_COLOR;
        }
        if (tick >= DAWN_END && tick <= DUSK_START) {
            return DAY_LIGHT_COLOR;
        }
    
        // Night
        if (DAWN_START - DUSK_END < 0 && ((tick >= DUSK_END && tick <= TICK_CYCLE) || tick <= DAWN_START)) {
            return NIGHT_LIGHT_COLOR;
        }
        if (tick >= DUSK_END && tick <= DAWN_START) {
            return NIGHT_LIGHT_COLOR;
        }
    
        // Day to Dusk
        if (DUSK - DUSK_START < 0 && ((tick >= DUSK_START && tick <= TICK_CYCLE) || tick <= DUSK)) {
            if (tick > 0 && 0 < DUSK) {
                tick += TICK_CYCLE;
            }
        
            value = changeIntervalTo01(tick, DAWN_START, DUSK + TICK_CYCLE);
            return glm::mix(DAY_LIGHT_COLOR, DAWN_DUSK_LIGHT_COLOR, value);
        }
        if (tick >= DUSK_START && tick <= DUSK) {
            value = changeIntervalTo01(tick, DUSK_START, DUSK);
            return glm::mix(DAY_LIGHT_COLOR, DAWN_DUSK_LIGHT_COLOR, value);
        }
    
        // Dusk to Night
        if (DUSK_END - DUSK < 0 && ((tick >= DUSK && tick <= TICK_CYCLE) || tick <= DUSK_END)) {
            if (tick > 0 && 0 < DUSK_END) {
                tick += TICK_CYCLE;
            }
        
            value = changeIntervalTo01(tick, DAWN_START, DUSK_END + TICK_CYCLE);
            return glm::mix(DAWN_DUSK_LIGHT_COLOR, NIGHT_LIGHT_COLOR, value);
        }
        if (tick >= DUSK && tick <= DUSK_END) {
            value = changeIntervalTo01(tick, DUSK, DUSK_END);
            return glm::mix(DAWN_DUSK_LIGHT_COLOR, NIGHT_LIGHT_COLOR, value);
        }
    
        // Night to Dawn
        if (DAWN - DAWN_START < 0 && ((tick >= DAWN_START && tick <= TICK_CYCLE) || tick <= DAWN)) {
            if (tick > 0 && 0 < DAWN) {
                tick += TICK_CYCLE;
            }
        
            value = changeIntervalTo01(tick, DAWN_START, DAWN + TICK_CYCLE);
            return glm::mix(NIGHT_LIGHT_COLOR, DAWN_DUSK_LIGHT_COLOR, value);
        }
        if (tick >= DAWN_START && tick <= DAWN) {
            value = changeIntervalTo01(tick, DAWN_START, DAWN);
            return glm::mix(NIGHT_LIGHT_COLOR, DAWN_DUSK_LIGHT_COLOR, value);
        }
    
        // Dawn to Day
        if (DAWN_END - DAWN < 0 && ((tick >= DAWN && tick <= TICK_CYCLE) || tick <= DAWN_END)) {
            if (tick > 0 && 0 < DAWN_END) {
                tick += TICK_CYCLE;
            }
        
            value = changeIntervalTo01(tick, DAWN, DAWN_END + TICK_CYCLE);
            return glm::mix(DAWN_DUSK_LIGHT_COLOR, DAY_LIGHT_COLOR, value);
        }
        else {
            value = changeIntervalTo01(tick, DAWN, DAWN_END);
            return glm::mix(DAWN_DUSK_LIGHT_COLOR, DAY_LIGHT_COLOR, value);
        }
    }
    
    
    GLfloat ConfigManager::getLightDirIntensity(GLint tick) {
        GLfloat value;
    
        // Day
        if (DUSK_START - DAWN_END < 0 && ((tick >= DAWN_END && tick <= TICK_CYCLE) || tick <= DUSK_START)) {
            return DAY_LIGHT_DIR_INTENSITY;
        }
        if (tick >= DAWN_END && tick <= DUSK_START) {
            return DAY_LIGHT_DIR_INTENSITY;
        }
    
        // Night
        if (DAWN_START - DUSK_END < 0 && ((tick >= DUSK_END && tick <= TICK_CYCLE) || tick <= DAWN_START)) {
            return NIGHT_LIGHT_DIR_INTENSITY;
        }
        if (tick >= DUSK_END && tick <= DAWN_START) {
            return NIGHT_LIGHT_DIR_INTENSITY;
        }
    
        // Day to Dusk
        if (DUSK - DUSK_START < 0 && ((tick >= DUSK_START && tick <= TICK_CYCLE) || tick <= DUSK)) {
            if (tick > 0 && 0 < DUSK) {
                tick += TICK_CYCLE;
            }
        
            value = changeIntervalTo01(tick, DAWN_START, DUSK + TICK_CYCLE);
            return glm::mix(DAY_LIGHT_DIR_INTENSITY, DAWN_DUSK_LIGHT_DIR_INTENSITY, value);
        }
        if (tick >= DUSK_START && tick <= DUSK) {
            value = changeIntervalTo01(tick, DUSK_START, DUSK);
            return glm::mix(DAY_LIGHT_DIR_INTENSITY, DAWN_DUSK_LIGHT_DIR_INTENSITY, value);
        }
    
        // Dusk to Night
        if (DUSK_END - DUSK < 0 && ((tick >= DUSK && tick <= TICK_CYCLE) || tick <= DUSK_END)) {
            if (tick > 0 && 0 < DUSK_END) {
                tick += TICK_CYCLE;
            }
        
            value = changeIntervalTo01(tick, DAWN_START, DUSK_END + TICK_CYCLE);
            return glm::mix(DAWN_DUSK_LIGHT_DIR_INTENSITY, NIGHT_LIGHT_DIR_INTENSITY, value);
        }
        if (tick >= DUSK && tick <= DUSK_END) {
            value = changeIntervalTo01(tick, DUSK, DUSK_END);
            return glm::mix(DAWN_DUSK_LIGHT_DIR_INTENSITY, NIGHT_LIGHT_DIR_INTENSITY, value);
        }
    
        // Night to Dawn
        if (DAWN - DAWN_START < 0 && ((tick >= DAWN_START && tick <= TICK_CYCLE) || tick <= DAWN)) {
            if (tick > 0 && 0 < DAWN) {
                tick += TICK_CYCLE;
            }
        
            value = changeIntervalTo01(tick, DAWN_START, DAWN + TICK_CYCLE);
            return glm::mix(NIGHT_LIGHT_DIR_INTENSITY, DAWN_DUSK_LIGHT_DIR_INTENSITY, value);
        }
        if (tick >= DAWN_START && tick <= DAWN) {
            value = changeIntervalTo01(tick, DAWN_START, DAWN);
            return glm::mix(NIGHT_LIGHT_DIR_INTENSITY, DAWN_DUSK_LIGHT_DIR_INTENSITY, value);
        }
    
        // Dawn to Day
        if (DAWN_END - DAWN < 0 && ((tick >= DAWN && tick <= TICK_CYCLE) || tick <= DAWN_END)) {
            if (tick > 0 && 0 < DAWN_END) {
                tick += TICK_CYCLE;
            }
        
            value = changeIntervalTo01(tick, DAWN, DAWN_END + TICK_CYCLE);
            return glm::mix(DAWN_DUSK_LIGHT_DIR_INTENSITY, DAY_LIGHT_DIR_INTENSITY, value);
        }
        else {
            value = changeIntervalTo01(tick, DAWN, DAWN_END);
            return glm::mix(DAWN_DUSK_LIGHT_DIR_INTENSITY, DAY_LIGHT_DIR_INTENSITY, value);
        }
    }
    
    
    GLfloat ConfigManager::getLightAmbIntensity(GLint tick) {
        GLfloat value;
    
        // Day
        if (DUSK_START - DAWN_END < 0 && ((tick >= DAWN_END && tick <= TICK_CYCLE) || tick <= DUSK_START)) {
            return DAY_LIGHT_AMB_INTENSITY;
        }
        if (tick >= DAWN_END && tick <= DUSK_START) {
            return DAY_LIGHT_AMB_INTENSITY;
        }
    
        // Night
        if (DAWN_START - DUSK_END < 0 && ((tick >= DUSK_END && tick <= TICK_CYCLE) || tick <= DAWN_START)) {
            return NIGHT_LIGHT_AMB_INTENSITY;
        }
        if (tick >= DUSK_END && tick <= DAWN_START) {
            return NIGHT_LIGHT_AMB_INTENSITY;
        }
    
        // Day to Dusk
        if (DUSK - DUSK_START < 0 && ((tick >= DUSK_START && tick <= TICK_CYCLE) || tick <= DUSK)) {
            if (tick > 0 && 0 < DUSK) {
                tick += TICK_CYCLE;
            }
        
            value = changeIntervalTo01(tick, DAWN_START, DUSK + TICK_CYCLE);
            return glm::mix(DAY_LIGHT_AMB_INTENSITY, DAWN_DUSK_LIGHT_AMB_INTENSITY, value);
        }
        if (tick >= DUSK_START && tick <= DUSK) {
            value = changeIntervalTo01(tick, DUSK_START, DUSK);
            return glm::mix(DAY_LIGHT_AMB_INTENSITY, DAWN_DUSK_LIGHT_AMB_INTENSITY, value);
        }
    
        // Dusk to Night
        if (DUSK_END - DUSK < 0 && ((tick >= DUSK && tick <= TICK_CYCLE) || tick <= DUSK_END)) {
            if (tick > 0 && 0 < DUSK_END) {
                tick += TICK_CYCLE;
            }
        
            value = changeIntervalTo01(tick, DAWN_START, DUSK_END + TICK_CYCLE);
            return glm::mix(DAWN_DUSK_LIGHT_AMB_INTENSITY, NIGHT_LIGHT_AMB_INTENSITY, value);
        }
        if (tick >= DUSK && tick <= DUSK_END) {
            value = changeIntervalTo01(tick, DUSK, DUSK_END);
            return glm::mix(DAWN_DUSK_LIGHT_AMB_INTENSITY, NIGHT_LIGHT_AMB_INTENSITY, value);
        }
    
        // Night to Dawn
        if (DAWN - DAWN_START < 0 && ((tick >= DAWN_START && tick <= TICK_CYCLE) || tick <= DAWN)) {
            if (tick > 0 && 0 < DAWN) {
                tick += TICK_CYCLE;
            }
        
            value = changeIntervalTo01(tick, DAWN_START, DAWN + TICK_CYCLE);
            return glm::mix(NIGHT_LIGHT_AMB_INTENSITY, DAWN_DUSK_LIGHT_AMB_INTENSITY, value);
        }
        if (tick >= DAWN_START && tick <= DAWN) {
            value = changeIntervalTo01(tick, DAWN_START, DAWN);
            return glm::mix(NIGHT_LIGHT_AMB_INTENSITY, DAWN_DUSK_LIGHT_AMB_INTENSITY, value);
        }
    
        // Dawn to Day
        if (DAWN_END - DAWN < 0 && ((tick >= DAWN && tick <= TICK_CYCLE) || tick <= DAWN_END)) {
            if (tick > 0 && 0 < DAWN_END) {
                tick += TICK_CYCLE;
            }
        
            value = changeIntervalTo01(tick, DAWN, DAWN_END + TICK_CYCLE);
            return glm::mix(DAWN_DUSK_LIGHT_AMB_INTENSITY, DAY_LIGHT_AMB_INTENSITY, value);
        }
        else {
            value = changeIntervalTo01(tick, DAWN, DAWN_END);
            return glm::mix(DAWN_DUSK_LIGHT_AMB_INTENSITY, DAY_LIGHT_AMB_INTENSITY, value);
        }
    }
    
    
    #pragma clang diagnostic pop
}
