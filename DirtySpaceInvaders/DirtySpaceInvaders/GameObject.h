#include "ConsoleRenderer.h"

class GameObject
{
public:
    char* m_objType = nullptr;
    Vector2D pos;
    unsigned char sprite;

    virtual void Update(class PlayField& world);
    bool DecreaseHealth();
};
