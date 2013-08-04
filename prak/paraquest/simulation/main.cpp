#include <iostream>

#include "world.hpp"
#include "utils.hpp"

int main(int argc, char **argv)
{
    //initRandom(generator, 0);

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, 4000);
    std::cout << distribution(generator) << std::endl;

    //std::cout << randInt(100) << std::endl;

    //World world(100, 100);

    //world.populate(100);
    //world.simulate(100);
}
