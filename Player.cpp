//
// Created by Alexandra Stefan on 06.12.2023.
//

#include "Player.h"
#include <vector>
#include "core/engine.h"
#include "utils/gl_utils.h"

void Player::setTx(float tx) {
    Player::tx = tx;
}

void Player::setTy(float ty) {
    Player::ty = ty;
}

void Player::setTz(float tz) {
    Player::tz = tz;
}

float Player::getTx() const {
    return tx;
}

float Player::getTy() const {
    return ty;
}

float Player::getTz() const {
    return tz;
}


float Player::getRotate() const {
    return rotate;
}

void Player::setRotate(float rotate) {
    Player::rotate = rotate;
}
float Player::getRotateTurela() const {
    return rotateTurela;
}

void Player::setRotateTurela(float rotateTurela) {
    Player::rotateTurela = rotateTurela;
}

Player::Player(float tx, float ty, float tz, float rotate, float rotateTurela) : tx(tx), ty(ty), tz(tz), rotate(rotate), rotateTurela(rotateTurela){}
// Movement methods
void Player::moveForward(float deltaTime) {
    tz -= cos(glm::radians(90.0f+rotate))*2*deltaTime; // Move along the local Z-axis (backward)
    tx -=  sin(glm::radians(90.0f+rotate))*2*deltaTime; // Move along the local X-axis
}

void Player::moveBackward(float deltaTime) {
    tz +=cos(glm::radians(90.0f+rotate))*2*deltaTime; // Move along the local Z-axis (forward)
    tx +=  sin(glm::radians(90.0f+rotate))*2*deltaTime; // Move along the local X-axis
}

void Player::rotateLeft(float deltaTime) {
    rotate += 50*deltaTime;
    rotateTurela +=50*deltaTime;
}

void Player::rotateRight(float deltaTime) {
    rotate -=50*deltaTime;
    rotateTurela -=50*deltaTime;
}

float Player::getHp() const {
    return hp;
}

void Player::setHp(float hp) {
    Player::hp = hp;
}







