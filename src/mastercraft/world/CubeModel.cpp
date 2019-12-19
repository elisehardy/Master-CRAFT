#include <mastercraft/world/CubeModel.hpp>


namespace mastercraft::world {
    
    CubeModel &CubeModel::get() {
        static CubeModel c;
        return c;
    }
    
    
    GLuint CubeModel::size() const {
        static constexpr GLuint n = sizeof(vertices) + sizeof(normals) + sizeof(textures);
        return n;
    }
    
    
    GLuint CubeModel::verticesCount() const {
        static constexpr GLuint n = sizeof(vertices) / sizeof(glm::vec3);
        return n;
    }
    
    
    GLuint CubeModel::normalsCount() const {
        static constexpr GLuint n = sizeof(normals) / sizeof(glm::vec3);
        return n;
    }
    
    
    GLuint CubeModel::texturesCount() const {
        static constexpr GLuint n = sizeof(textures) / sizeof(glm::vec2);
        return n;
    }
    
    
    GLuint CubeModel::indexesCount() const{
        static constexpr GLuint n = sizeof(indexes) / sizeof(GLuint);
        return n;
    }
}
