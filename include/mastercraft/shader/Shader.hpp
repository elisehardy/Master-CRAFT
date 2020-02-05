#ifndef MASTERCRAFT_SHADER_HPP
#define MASTERCRAFT_SHADER_HPP

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include <mastercraft/util/INonCopyable.hpp>
#include <mastercraft/shader/uniform/IUniform.hpp>


namespace mastercraft::shader {
    
    class Shader : public util::INonCopyable {
        protected:
            std::unordered_map<std::string, std::shared_ptr<IUniform>> uniforms;
            GLuint programId;
            GLuint vsId;
            GLuint fsId;
        
        public:
            
            Shader() = default;
            
            Shader(const std::string &vsPath, const std::string &fsPath);
        
            ~Shader();
            
            void addUniform(const std::string &name, UniformType type);
            
            void loadUniform(const std::string &name, const void* value);
            
            void use() const;
            
            void stop() const;
    };
}

#endif // MASTERCRAFT_SHADER_HPP

