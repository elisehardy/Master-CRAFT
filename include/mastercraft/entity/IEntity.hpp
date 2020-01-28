#ifndef MASTERCRAFT_IENTITY_HPP
#define MASTERCRAFT_IENTITY_HPP

#include <glm/vec3.hpp>
#include <GL/glew.h>


namespace mastercraft::entity {
    
    class IEntity :
        glm::vec3 position;
        GLfloat rotation
        
        
        GLuint update();
    
        GLuint render();
}


#endif //MASTERCRAFT_IENTITY_HPP
