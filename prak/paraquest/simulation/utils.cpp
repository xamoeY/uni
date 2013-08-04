#include "utils.hpp"

void initRandom(std::default_random_engine generator, int seed)
{
    if (seed == 0)
        generator.seed(std::default_random_engine::default_seed);
    else
        generator.seed(seed);
}

int randInt(int low, int high)
{
    //std::uniform_int_distribution<int> distribution(low, high);
    //return distribution(generator);
}

int randInt(int high)
{
    //std::uniform_int_distribution<int> distribution(0, high);
    //return distribution(generator);

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, high);
    return distribution(generator);
}
