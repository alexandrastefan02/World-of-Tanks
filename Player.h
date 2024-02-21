//
// Created by Alexandra Stefan on 06.12.2023.
//

#ifndef GFXFRAMEWORK_PLAYER_H
#define GFXFRAMEWORK_PLAYER_H


#include <vector>
#include "utils/gl_utils.h"
#include "core/engine.h"
#include "Proiectil.h"

class Player {
private:
    float tx;
    float ty;
    float tz;
    float rotate;
    float rotateTurela;
    float hp = 5;
public:
    float getHp() const;

    void setHp(float hp);

    std::vector<Proiectil> munitie;
    float getRotateTurela() const;

    void setRotateTurela(float rotateTurela);

    void setTx(float tx);

    void setTy(float ty);

    void setTz(float tz);

    float getTx() const;

    float getTy() const;

    float getTz() const;

    float getRotate() const;

    void setRotate(float rotate);

    Player(float tx, float ty, float tz, float rotate, float rotateTurela);

    // Movement methods
    void moveForward(float deltaTime);
    void moveBackward( float deltaTime);
    void rotateLeft(float deltaTime);
    void rotateRight(float deltaTime);

};



#endif //GFXFRAMEWORK_PLAYER_H
