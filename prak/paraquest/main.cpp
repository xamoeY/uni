#include <iostream>

#include "world.hpp"

int main()
{
    World world;
    world.populate(100);
    world.simulate(100);
    return 0;
}
