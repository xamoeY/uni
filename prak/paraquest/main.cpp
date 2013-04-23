#include <iostream>

#include "world.hpp"

int main()
{
    World world(100, 100);
    world.populate(100);
    world.simulate(100);
    return 0;
}
