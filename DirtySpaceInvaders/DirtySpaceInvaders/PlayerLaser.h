#pragma once
#include "GameObject.h"

class PlayerLaser : public GameObject
{
public:
    PlayerLaser() { m_objType = new char[64]; strcpy(m_objType, "PlayerLaser"); sprite = RS_PlayerLaser; }
    ~PlayerLaser() { delete[] m_objType; }

    void Update(PlayField& world);
};
