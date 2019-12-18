#pragma once

#include <GL/glew.h>
#include <glimac/Shader.hpp>
#include <glimac/FilePath.hpp>


namespace glimac {
    
    class Program {
        public:
            Program();
            
            Program(Program &&rvalue) noexcept;
            
            ~Program();
            
            Program &operator=(Program &&rvalue) noexcept;
            
            [[nodiscard]] GLuint getGLId() const;
            
            [[nodiscard]] std::string getInfoLog() const;
            
            void attachShader(const Shader &shader);
            
            bool link();
            
            void use() const;
        
        private:
            GLuint m_nGLId;
            
            Program(const Program &);
            
            Program &operator=(const Program &);
    };
    
    
    
    /**
     * Build a GLSL program from source code
     */
    Program buildProgram(const GLchar *vsSrc, const GLchar *fsSrc);
    
    /**
     * Load source code from files and build a GLSL program
     */
    Program loadProgram(const FilePath &vsFile, const FilePath &fsFile);
}
