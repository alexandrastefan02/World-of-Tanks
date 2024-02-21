#include <random>
#include <map>
#include <string>
#include <iostream>
#pragma once
using namespace std;

enum class MovementState
{
    GoingForward,
    GoingBackward,
    InPlaceRotationLeft,
    InPlaceRotationRight
};