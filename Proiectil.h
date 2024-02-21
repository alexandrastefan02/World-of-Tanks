//
// Created by Alexandra Stefan on 11.12.2023.
//

#ifndef GFXFRAMEWORK_PROIECTIL_H
#define GFXFRAMEWORK_PROIECTIL_H


#include "glm/detail/type_vec3.hpp"
#include "glm/vec3.hpp"

class Proiectil {
private:
    float px;
    float py;
    float pz;
    float rotate;
    float ttl;
    bool render;
    bool hit=false;
public:
    bool isHit() const;

    void setHit(bool hit);

    bool isRender() const;

    void setRender(bool render);

    float getRotate() const;

    float getTtl() const;

    void setTtl(float ttl);

    void setRotate(float rotate);

    float getPx() const;

    void setPx(float px);

    float getPy() const;

    void setPy(float py);

    float getPz() const;

    void setPz(float pz);

    Proiectil(float px, float py, float pz, float rotate, float ttl, bool render);

    void moveForward(float deltaTime);
    glm::vec3 getForwardVector(float deltatime);
    glm::vec3 getDirection() const;

    glm::vec3 getForward();
};


#endif //GFXFRAMEWORK_PROIECTIL_H
