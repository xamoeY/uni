#include <iostream>

#include "world.hpp"
#include "utils.hpp"

int main(int argc, char **argv)
{
    initRandom(0);

    World world(10, 10);

    world.populate(10);
    world.simulate(10);
}
