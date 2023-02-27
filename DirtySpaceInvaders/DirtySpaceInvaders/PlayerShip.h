#pragma once
#include "GameObject.h"

class PlayerShip : public GameObject
{
public:
    PlayerShip(); 
    ~PlayerShip(); 

    void Update(PlayField& world);
};