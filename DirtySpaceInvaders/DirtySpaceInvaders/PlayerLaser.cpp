#include "PlayerLaser.h"
#include "PlayField.h"

void PlayerLaser::Update(PlayField& world)
{
    bool deleted = false;
    pos.y -= 1.f;
    if (pos.y < 0)
    {
        deleted = true;
    }

    if (deleted)
    {
        world.DespawnLaser(this);
        //delete this;
    }
}
