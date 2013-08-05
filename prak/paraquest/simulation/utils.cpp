#include "utils.hpp"

std::random_device rd;
std::mt19937 generator(rd());

void initRandom(int seed)
{
    if (seed != 0)
        generator.seed(seed);
}

int randInt(int low, int high)
{
    std::uniform_int_distribution<int> distribution(low, high);
    return distribution(generator);
}

int randInt(int high)
{
    std::uniform_int_distribution<int> distribution(0, high);
    return distribution(generator);
}
