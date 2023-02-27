#pragma once
#include "GameObject.h"

class AlienLaser : public GameObject
{
public:
    AlienLaser();
    ~AlienLaser();

    void Update(PlayField& world);
};
