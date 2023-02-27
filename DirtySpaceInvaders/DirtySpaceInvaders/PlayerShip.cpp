#include "PlayerShip.h"
#include "PlayField.h"
#include "PlayerLaser.h"

PlayerShip::PlayerShip()
{
    m_objType = new char[64]; strcpy(m_objType, "PlayerShip"); sprite = RS_Player;
}

PlayerShip::~PlayerShip()
{
    delete m_objType;
}

void PlayerShip::Update(PlayField& world)
{
    if(!world.controllerInput)
        return;
    if (world.controllerInput->Left())
        pos.x -= 1;
    else if (world.controllerInput->Right())
        pos.x += 1;

    if (world.controllerInput->Fire() && world.PlayerLasers > 0)
    {
        //Spawn laser
        GameObject& newLaser = *(new PlayerLaser);
        newLaser.pos = pos;
        world.SpawnLaser(&newLaser);
    }
}
