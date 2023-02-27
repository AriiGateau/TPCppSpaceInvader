#pragma once
#include "Input.h"

class RndInput : public Input
{
public:
    virtual bool Left();
    virtual bool Right();
    virtual bool Fire();
};
