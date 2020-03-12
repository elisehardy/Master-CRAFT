//
// Created by ehardy on 3/2/20.
//
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

#include <mastercraft/entity/Magie2.hpp>
#include <mastercraft/game/Game.hpp>


namespace mastercraft::entity {

    Magie2::Magie2() :
            texture(util::Image::loadPNG("../assets/entity/magie/magie.png", 250, 253)),
            position(glm::vec3(0, game::ConfigManager::GEN_MAX_HEIGHT + 1, 0)), pitch(0.0), yaw(M_PIf32)
    {
            computeDirectionVectors();




        this->shader = std::make_unique<shader::ShaderTexture>(
                "../shader/npc.vs.glsl", "../shader/npc.fs.glsl"
        );
        this->shader->addUniform("uMV", shader::UNIFORM_MATRIX_4F);
        this->shader->addUniform("uMVP", shader::UNIFORM_MATRIX_4F);
        this->shader->addUniform("uNormal", shader::UNIFORM_MATRIX_4F);
        this->shader->addUniform("uLightPosition", shader::UNIFORM_3_F);
        this->shader->addUniform("uLightColor", shader::UNIFORM_3_F);
        this->shader->addUniform("uLightDirIntensity", shader::UNIFORM_1_F);
        this->shader->addUniform("uLightAmbIntensity", shader::UNIFORM_1_F);

        this->texture.bind();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        this->texture.unbind();

        glGenBuffers(1, &this->vbo);
        glGenVertexArrays(1, &this->vao);
    }


    Magie2::~Magie2() {
        glDeleteBuffers(1, &this->vbo);
        glDeleteVertexArrays(1, &this->vao);
    }

    void Magie2::init() {
        game::Game *game = game::Game::getInstance();
        glm::mat4 rinit = glm::rotate(glm::mat4(1.f), 3.f, glm::vec3(0.f, 1.f, 0.f));


        glm::vec3 nextPosition = game->camera->getPosition();


        nextPosition.z +=1;
        this->position = rinit *glm::vec4(nextPosition,1);


    }

    void Magie2::init2() {
        game::Game *game = game::Game::getInstance();
        glm::mat4 rinit = glm::rotate(glm::mat4(1.f), 3.f, glm::vec3(0.f, 1.f, 0.f));


        glm::vec3 nextPosition = game->camera->getPosition();


        nextPosition.z +=0;
        this->position = rinit *glm::vec4(nextPosition,1);


    }


    GLuint Magie2::update() {
        //game::Game *game = game::Game::getInstance();
        //GLfloat yaw = std::atan2(this->direction.x, this->direction.z);
        //glm::mat4 rY = glm::rotate(glm::mat4(1.f), yaw-3.f, glm::vec3(0.f, 1.f, 0.f));
        //glm::mat4 rX = glm::rotate( glm::mat4(1.f), pitch, glm::vec3(0.f, 0.f, 1.f));
        glm::mat4 scale = glm::scale(glm::mat4(0.1f), glm::vec3(1.5f, 1.5f, 1.5f));


        glm::mat4 translate = glm::translate(glm::mat4(1.f), glm::vec3(0,1,1));
        glm::vec3 positionP ;


       // this->position = pos;
        glm::vec3 vertices[36];
        for (GLuint i = 0; i < 36; i++) {
            positionP =
                    glm::vec3(translate*scale *glm::vec4(this->vertices[i] - glm::vec3(0.5), 1))  + glm::vec3(glm::vec4(this->position,1));
            positionP -= glm::vec3(0, 0.6, 0);
            vertices[i] = positionP;
        }




        // Fill the VBO
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Set the VAO
        glBindVertexArray(this->vao);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);


        return 1;
    }


    GLuint Magie2::render() {
        game::Game *game = game::Game::getInstance();
        glm::mat4 MVMatrix = game->camera->getViewMatrix();


        //        glm::mat4 MVMatrix = glm::mat4(glm::mat3(game->camera->getViewMatrix())); // Remove translation from the MV
        glm::mat4 MVPMatrix = game->camera->getProjMatrix() * MVMatrix;
        glm::mat4 normalMatrix = glm::transpose(glm::inverse(MVMatrix));

        glm::vec3 lightPos = glm::vec3(MVMatrix * glm::vec4(game->sun->getPosition(), 0));
        glm::vec3 lightColor = game::ConfigManager::getLightColor(game->tickCycle);
        GLfloat lightDirIntensity = game::ConfigManager::getLightDirIntensity(game->tickCycle);
        GLfloat lightAmbIntensity = game::ConfigManager::getLightAmbIntensity(game->tickCycle);

        this->shader->use();

        this->shader->loadUniform("uMV", glm::value_ptr(MVMatrix));
        this->shader->loadUniform("uMVP", glm::value_ptr(MVPMatrix));
        this->shader->loadUniform("uNormal", glm::value_ptr(normalMatrix));
        this->shader->loadUniform("uLightPosition", glm::value_ptr(lightPos));
        this->shader->loadUniform("uLightColor", glm::value_ptr(lightColor));
        this->shader->loadUniform("uLightDirIntensity", &lightDirIntensity);
        this->shader->loadUniform("uLightAmbIntensity", &lightAmbIntensity);
        this->texture.bind();
        glBindVertexArray(this->vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        this->texture.unbind();
        this->shader->stop();
        return 1;
    }


    glm::vec3 Magie2::getPosition() {
        return this->position;
    }

    c3ga::Mvec<double> Magie2::getSphereDual(){
        return dualSphere(double(this->position.x), double(this->position.y), double(this->position.z), double(0.15));
    }

    c3ga::Mvec<double> Magie2::getSphereDual2(glm::vec3 t_position){
        return dualSphere(double(t_position.x), double(t_position.y), double(t_position.z), double(0.15));
    }

    c3ga::Mvec<double> Magie2::getSphere(){
        glm::vec3 p1 = vertices[0];
        glm::vec3 p2 = vertices[1];
        glm::vec3 p3 = vertices[35];
        glm::vec3 p4 = vertices[34];
        c3ga::Mvec<double> sphere = point(double(p1.x),double(p1.y),double(p1.z)) ^ point(double(p2.x),double(p2.y),double(p2.z)) ^point(double(p3.x),double(p3.y),double(p3.z)) ^point(double(p4.x),double(p4.y),double(p4.z));
        return sphere;
    }

    GLboolean Magie2::isTouch(c3ga::Mvec<double> sphereDual){
        c3ga::Mvec<double> sphereDual2 = this->getSphereDual();
        c3ga::Mvec<double> intersection = (sphereDual2 ^ sphereDual).dual();
        double radius  = sqrt(intersection * intersection);
        auto cercle = (radius/(radius*c3ga::Ei)) * (radius/(radius*c3ga::Ei));
        if(cercle >=0.0){
            return true;
        }
        return false;
    }



    GLboolean Magie2::isTouch2(c3ga::Mvec<double> sphereDual, c3ga::Mvec<double> sphereDual2){

        c3ga::Mvec<double> intersection = (sphereDual2 ^ sphereDual).dual();
        double radius  = sqrt(intersection * intersection);
        auto cercle = (radius/(radius*c3ga::Ei)) * (radius/(radius*c3ga::Ei));
        if(cercle >=0.0){
            return true;
        }
        return false;
    }

    void Magie2::rotateLeft(float degrees) {
        this->yaw += glm::radians(degrees * game::Game::getInstance()->configManager->getMouseSensitivity());
        computeDirectionVectors();
    }

    void Magie2::computeDirectionVectors() {
        this->frontVector = { cos(this->pitch) * sin(this->yaw), sin(this->pitch), cos(this->pitch) * cos(this->yaw) };
        this->leftVector = { sin(this->yaw + M_PI_2f32), 0.f, cos(this->yaw + M_PI_2f32) };
        this->upVector = glm::cross(this->frontVector, this->leftVector);
    }


    void Magie2::moveLeft(float delta) {
        this->position += delta * this->leftVector;
    }


    void Magie2::moveForward(float delta) {
        this->position += delta * this->frontVector;
    }


    void Magie2::moveUp(float delta) {
        this->position += delta * this->upVector;
    }





    void Magie2::rotateUp(float degrees) {
        this->pitch += glm::radians(degrees * game::Game::getInstance()->configManager->getMouseSensitivity());
        this->pitch = std::max(std::min(this->pitch, M_PI_2f32), -M_PI_2f32);
        computeDirectionVectors();
    }


    void Magie2::setPosition(GLfloat x, GLfloat y, GLfloat z) {
        this->position = { x, y, z };
    }

    void Magie2::setPositionheight(GLfloat y) {
        this->position.y +=  y;
    }

}

