#ifndef UTILS_HPP
#define UTILS_HPP

#include <random>

static std::default_random_engine generator;

void initRandom(int seed);

int randInt(int low, int high);

int randInt(int high);

#endif // UTILS_HPP
