#include "PlayField.h"

void PlayField::Update()
{
    // Update list of active objects in the world
    for (auto it : GameObjects())
    {
        it->Update(*this);
    }
}

GameObject* PlayField::GetPlayerObject()
{
    auto it = std::find_if(gameObjects.begin(), gameObjects.end(), [](GameObject* in) { return (strcmp(in->m_objType, "playerShip") == 0); });
    if (it != gameObjects.end())
        return (*it);
    else
        return nullptr;
}

void PlayField::SpawnLaser(GameObject* newObj)
{
    if (strcmp(newObj->m_objType, "AlienLaser") == 0)
        AlienLasers--;

    else if (strcmp(newObj->m_objType, "PlayerLaser") == 0)
        PlayerLasers--;

    AddObject(newObj);
}

void PlayField::DespawnLaser(GameObject* newObj)
{
    if (strcmp(newObj->m_objType, "AlienLaser") == 0)
        AlienLasers++;

    else if (strcmp(newObj->m_objType, "PlayerLaser") == 0)
        PlayerLasers++;

    RemoveObject(newObj);
}

void PlayField::AddObject(GameObject* newObj)
{
    gameObjects.push_back(newObj);
}

void PlayField::RemoveObject(GameObject* newObj)
{
    auto it = std::find(gameObjects.begin(), gameObjects.end(), newObj); // , [&](GameObject* in) { return (in == newObj); });
    delete* it;
    //gameObjects.erase(it);
}
