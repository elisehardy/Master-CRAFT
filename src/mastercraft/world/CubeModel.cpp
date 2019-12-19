#include <mastercraft/world/CubeModel.hpp>


namespace mastercraft::world {
    
    CubeModel &CubeModel::get() {
        static CubeModel c;
        return c;
    }
    
    
    GLuint CubeModel::size() const {
        static constexpr GLuint n = sizeof(this->vertices) + sizeof(this->normals) + sizeof(this->textures);
        return n;
    }
    
    
    GLuint CubeModel::verticesCount() const {
        static constexpr GLuint n = sizeof(this->vertices) / sizeof(glm::vec3);
        return n;
    }
    
    
    GLuint CubeModel::normalsCount() const {
        static constexpr GLuint n = sizeof(this->normals) / sizeof(glm::vec3);
        return n;
    }
    
    
    GLuint CubeModel::texturesCount() const {
        static constexpr GLuint n = sizeof(this->textures) / sizeof(glm::vec2);
        return n;
    }
    
    
    GLuint CubeModel::indexesCount() const{
        static constexpr GLuint n = sizeof(this->indexes) / sizeof(GLuint);
        return n;
    }
    
    
    void CubeModel::load(GLuint &vbo, GLuint &vao, GLuint &ibo) const {
        static const GLuint VERTEX_ATTR_POSITION = 0;
        static const GLuint VERTEX_ATTR_NORMAL = 1;
        static const GLuint VERTEX_ATTR_TEXTURE = 2;
    
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, size(), this, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->indexes), this->indexes, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(
                VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3),
                (const GLvoid *) (offsetof(CubeModel, vertices))
        );
        glVertexAttribPointer(
                VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3),
                (const GLvoid *) (offsetof(CubeModel, normals))
        );
        glVertexAttribPointer(
                VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2),
                (const GLvoid *) (offsetof(CubeModel, textures))
        );
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}
