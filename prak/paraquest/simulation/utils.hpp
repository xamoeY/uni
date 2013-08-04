#ifndef UTILS_HPP
#define UTILS_HPP

#include <random>

void initRandom(std::default_random_engine generator, int seed);

int randInt(int low, int high);

int randInt(int high);

#endif // UTILS_HPP
