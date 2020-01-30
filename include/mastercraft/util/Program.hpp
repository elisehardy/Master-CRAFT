#ifndef MASTERCRAFT_PROGRAM_HPP
#define MASTERCRAFT_PROGRAM_HPP

#include <GL/glew.h>

#include <glimac/Shader.hpp>
#include <glimac/FilePath.hpp>

#include <mastercraft/util/INonCopyable.hpp>


namespace mastercraft::util {
    
    class Program : public INonCopyable {
        private:
            GLuint id;
            
            [[nodiscard]] std::string getInfoLog() const;
            
            void attachShader(const glimac::Shader &shader);
            
            bool link();
        
        public:
            
            Program(const glimac::FilePath &vsPath, const glimac::FilePath &fsPath);
            
            ~Program();
            
            [[nodiscard]] GLuint getId() const;
            
            void use() const;
            
            void stop() const;
    };
}

#endif // MASTERCRAFT_PROGRAM_HPP
