//
// Created by Alexandra Stefan on 11.12.2023.
//

#include "Proiectil.h"
#include "glm/trigonometric.hpp"
#include "utils/glm_utils.h"

float Proiectil::getPx() const {
    return px;
}

void Proiectil::setPx(float px) {
    Proiectil::px = px;
}

float Proiectil::getPy() const {
    return py;
}

void Proiectil::setPy(float py) {
    Proiectil::py = py;
}

float Proiectil::getPz() const {
    return pz;
}

void Proiectil::setPz(float pz) {
    Proiectil::pz = pz;
}
void Proiectil::moveForward(float deltaTime) {
    pz -= cos(glm::radians(90.0f+rotate))*deltaTime; // Move along the local Z-axis (backward)
    px -=  sin(glm::radians(90.0f+rotate))*deltaTime; // Move along the local X-axis
}
glm::vec3 Proiectil:: getDirection() const {
    // Assuming Y-axis is the up direction
    float directionX = cos(90.0f+rotate);
    float directionZ = sin(90.0f+rotate);

    // Return a normalized 3D vector
    return glm::vec3(directionX, py, directionZ);
}

Proiectil::Proiectil(float px, float py, float pz, float rotate, float ttl, bool render ): px(px), py(py), pz(pz), rotate(rotate), ttl(ttl), render(render) {}

float Proiectil::getRotate() const {
    return rotate;
}
glm::vec3 Proiectil::getForward(){
    glm::vec3 forward     = glm::normalize(glm::vec3(0.0f, 0.58f, 0.0f) - glm::vec3(px, py, pz));
    return forward;
}
void Proiectil::setRotate(float rotate) {
    Proiectil::rotate = rotate;
}

glm::vec3 Proiectil::getForwardVector(float deltatime) {
    // Convert the rotation from degrees to radians
    float angleInRadians = glm::radians(rotate);

    // Compute the forward vector using trigonometric functions
    px += cos(angleInRadians)*deltatime;
   // py = 0.58f; // Assuming the projectile moves only in the x-z plane
    pz += sin(angleInRadians)*deltatime;

    return glm::vec3(px, py, pz);
}

float Proiectil::getTtl() const {
    return ttl;
}

void Proiectil::setTtl(float ttl) {
    Proiectil::ttl = ttl;
}

bool Proiectil::isRender() const {
    return render;
}

void Proiectil::setRender(bool render) {
    Proiectil::render = render;
}

bool Proiectil::isHit() const {
    return hit;
}

void Proiectil::setHit(bool hit) {
    Proiectil::hit = hit;
}
