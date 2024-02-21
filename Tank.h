//
// Created by Alexandra Stefan on 13.12.2023.
//
#include "state_automaton.h"
#include "glm/trigonometric.hpp"
#include "Proiectil.h"
#ifndef GFXFRAMEWORK_TANK_H
#define GFXFRAMEWORK_TANK_H

#include "Proiectil.h"
class Tank {
private:
    float x;
    float y;
    float z;
    float rotate;
    float time;
    MovementState state;
    MovementState next_state;
    float angle;
    float ttl;
    float timeSinceLastProj;
    float hp=5;
    bool addedToScore=false;
public:
    bool isAddedToScore() const;

    void setAddedToScore(bool addedToScore);

    float getHp() const;

    void setHp(float hp);

    float getTimeSinceLastProj() const;

    void setTimeSinceLastProj(float timeSinceLastProj);

    const vector<Proiectil> &getMunitie() const;

    void setMunitie(const vector<Proiectil> &munitie);

    float getTtl() const;

    void setTtl(float ttl);

    vector<Proiectil> munitie;
    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    float getZ() const;

    void setZ(float z);

    float getRotate() const;

    void setRotate(float rotate);

    float getTime() const;

    void setTime(float time);

    MovementState getState() const;

    void setState(MovementState state);

    MovementState getNextState() const;

    void setNextState(MovementState nextState);

    float getAngle() const;

    void setAngle(float angle);
    void moveForward(float deltaTime);

    void moveBackward(float deltaTime);

    void rotateLeft(float deltaTime);

    void rotateRight(float deltaTime);

    Tank(float x, float y, float z, float rotate, float time, MovementState state, MovementState nextState,
         float angle, float timeSinceLastProj);

};


#endif //GFXFRAMEWORK_TANK_H
