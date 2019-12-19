#ifndef MASTERCRAFT_PROGRAM_HPP
#define MASTERCRAFT_PROGRAM_HPP

#include <glimac/Shader.hpp>
#include <glimac/FilePath.hpp>
#include <GL/glew.h>


namespace mastercraft::util {
    
    class Program {
        private:
            GLuint m_nGLId;
            
            Program(const Program &);
            
            Program &operator=(const Program &);
            
            [[nodiscard]] std::string getInfoLog() const;
        
            void attachShader(const glimac::Shader &shader);
        
            bool link();
        
        public:
        
            Program();
        
            Program(Program &&rvalue) noexcept;
        
            ~Program();
        
            Program &operator=(Program &&rvalue) noexcept;
        
            static Program loadProgram(const glimac::FilePath &vsFile, const glimac::FilePath &fsFile);
            
            [[nodiscard]] GLuint getGLId() const;
        
            void use() const;
    };
}

#endif // MASTERCRAFT_PROGRAM_HPP
