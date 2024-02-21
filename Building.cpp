//
// Created by Alexandra Stefan on 12.12.2023.
//

#include "Building.h"

float Building::getWidth() const {
    return width;
}

void Building::setWidth(float width) {
    Building::width = width;
}

Building::Building(float width, float bx, float by, float bz) : width(width), bx(bx), by(by), bz(bz) {}

float Building::getBx() const {
    return bx;
}

void Building::setBx(float bx) {
    Building::bx = bx;
}

float Building::getBy() const {
    return by;
}

void Building::setBy(float by) {
    Building::by = by;
}

float Building::getBz() const {
    return bz;
}

void Building::setBz(float bz) {
    Building::bz = bz;
}
