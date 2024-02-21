//
// Created by Alexandra Stefan on 13.12.2023.
//

#include "Tank.h"

float Tank::getX() const {
    return x;
}

void Tank::setX(float x) {
    Tank::x = x;
}

float Tank::getY() const {
    return y;
}

void Tank::setY(float y) {
    Tank::y = y;
}

float Tank::getZ() const {
    return z;
}

void Tank::setZ(float z) {
    Tank::z = z;
}

float Tank::getRotate() const {
    return rotate;
}

void Tank::setRotate(float rotate) {
    Tank::rotate = rotate;
}

float Tank::getTime() const {
    return time;
}

void Tank::setTime(float time) {
    Tank::time = time;
}

MovementState Tank::getState() const {
    return state;
}

void Tank::setState(MovementState state) {
    Tank::state = state;
}

MovementState Tank::getNextState() const {
    return next_state;
}

void Tank::setNextState(MovementState nextState) {
    next_state = nextState;
}

float Tank::getAngle() const {
    return angle;
}

void Tank::setAngle(float angle) {
    Tank::angle = angle;
}
void Tank::moveForward(float deltaTime) {
    z -= cos(glm::radians(90.0f+rotate))*deltaTime; // Move along the local Z-axis (backward)
    x -=  sin(glm::radians(90.0f+rotate))*deltaTime; // Move along the local X-axis
}

void Tank::moveBackward(float deltaTime) {
    z +=cos(glm::radians(90.0f+rotate))*deltaTime; // Move along the local Z-axis (forward)
    x +=  sin(glm::radians(90.0f+rotate))*deltaTime; // Move along the local X-axis
}

void Tank::rotateLeft(float deltaTime) {
    rotate += 50*deltaTime;
    //rotateTurela +=50*deltaTime;
}

void Tank::rotateRight(float deltaTime) {
    rotate -=50*deltaTime;
    //rotateTurela -=50*deltaTime;
}

Tank::Tank(float x, float y, float z, float rotate, float time, MovementState state, MovementState nextState,
           float angle, float timeSinceLastProj) : x(x), y(y), z(z), rotate(rotate), time(time), state(state), next_state(nextState),
                          angle(angle),timeSinceLastProj(timeSinceLastProj)  {}

float Tank::getTtl() const {
    return ttl;
}

void Tank::setTtl(float ttl) {
    Tank::ttl = ttl;
}

float Tank::getTimeSinceLastProj() const {
    return timeSinceLastProj;
}

void Tank::setTimeSinceLastProj(float timeSinceLastProj) {
    Tank::timeSinceLastProj = timeSinceLastProj;
}

const vector<Proiectil> &Tank::getMunitie() const {
    return munitie;
}

void Tank::setMunitie(const vector<Proiectil> &munitie) {
    Tank::munitie = munitie;
}

float Tank::getHp() const {
    return hp;
}

void Tank::setHp(float hp) {
    Tank::hp = hp;
}

bool Tank::isAddedToScore() const {
    return addedToScore;
}

void Tank::setAddedToScore(bool addedToScore) {
    Tank::addedToScore = addedToScore;
}
