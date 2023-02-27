#pragma once
#include "GameObject.h"

class Alien : public GameObject
{
public:
    Alien(); 
    ~Alien(); 

private:
    float health = 1.f;
    float energy = 0.f;
    float direction = 1.f;
    float velocity = 0.5f;

    bool DecreaseHealth();

    void Update(PlayField& world);
};
