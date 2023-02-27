#include "Alien.h"
#include <random>
#include "PlayField.h"
#include "AlienLaser.h"

std::default_random_engine rGen;
typedef std::uniform_real_distribution<float> floatRand;

Alien::Alien()
{
    m_objType = new char[64]; strcpy(m_objType, "AlienShip"); sprite = RS_Alien;
}

Alien::~Alien()
{
    delete m_objType;
}

bool Alien::DecreaseHealth()
{
    health -= 1.f; return health <= 0;
}

void Alien::Update(PlayField& world)
{
    pos.x += direction * velocity;
    // Border check
    if (pos.x < 0 || pos.x >= world.bounds.x - 1)
    {
        direction = -direction;
        pos.y += 1;
    }

    // Border check vertical:
    if (pos.y >= world.bounds.y - 1)
    {
        // kill player
        GameObject* player = world.GetPlayerObject();
        if (pos.IntCmp(player->pos))
        {
            world.RemoveObject(player);
        }
    }

    floatRand fireRate(0, 1);
    if (fireRate(rGen) < 0.5 && world.AlienLasers > 0)
    {
        //Spawn laser
        GameObject& newLaser = *(new AlienLaser);
        newLaser.pos = pos;
        world.SpawnLaser(&newLaser);
    }
}

