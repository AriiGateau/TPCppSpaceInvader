#include "RndInput.h"
#include <random>

std::default_random_engine rGen;
typedef std::uniform_int_distribution<int> intRand;
typedef std::uniform_real_distribution<float> floatRand;

bool RndInput::Left()
{
    floatRand keyRate(0, 1); return (keyRate(rGen) < 0.3f);
}

bool RndInput::Right()
{
    floatRand keyRate(0, 1); return (keyRate(rGen) < 0.4f);
}

bool RndInput::Fire()
{
    floatRand keyRate(0, 1); return (keyRate(rGen) < 0.5f);
}
