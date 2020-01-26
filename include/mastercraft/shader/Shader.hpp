#ifndef MASTERCRAFT_SHADER_HPP
#define MASTERCRAFT_SHADER_HPP

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include <mastercraft/util/Program.hpp>
#include <mastercraft/util/INonCopyable.hpp>
#include <mastercraft/shader/uniform/IUniform.hpp>


namespace mastercraft::shader {
    
    class Shader : public util::INonCopyable {
        protected:
            std::unordered_map<std::string, std::shared_ptr<IUniform>> uniforms;
            util::Program program;
        
        public:
            
            Shader() = default;
            
            Shader(const glimac::FilePath &vsFile, const glimac::FilePath &fsFile);
            
            void addUniform(const std::string &name, UniformType type);
            
            void loadUniform(const std::string &name, const void* value);
            
            void use() const;
    };
}

#endif // MASTERCRAFT_SHADER_HPP

