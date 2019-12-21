#ifndef MASTERCRAFT_FREEFLYCAMERA_HPP
#define MASTERCRAFT_FREEFLYCAMERA_HPP

#include <glm/mat4x4.hpp>
#include <GL/glew.h>


namespace mastercraft::world {

    class FreeflyCamera {
    private:
        float m_fPhi; //coord vecteur F
        float m_fTheta; //coord vecteur F
        glm::vec3 m_Position; //position camera
        glm::vec3 m_FrontVector; //vecteur F
        glm::vec3 m_LeftVector; //vecteur L
        glm::vec3 m_UpVector; //vecteur U


    public:
        // Constructeur
        FreeflyCamera();

        // déplacer la position de la caméra respectivement le long du vecteur L⃗
        void moveLeft(float t);

        // déplacer la position de la caméra respectivement le long du vecteur F⃗
        void moveFront(float t);

        // modifiant l'angle de rotation m_fPhi
        void rotateLeft(float degrees);

        // modifiant l'angle de rotation m_fTheta
        void rotateUp(float degrees);

        // calcule et renvoi la matrice View associée à la caméra
        glm::mat4 getViewMatrix() const;

        void computeDirectionVectors();


    };

}

#endif // MASTERCRAFT_FREEFLYCAMERA_HPP
