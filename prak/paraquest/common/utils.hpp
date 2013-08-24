#ifndef UTILS_HPP
#define UTILS_HPP

#include <random>

void initRandom(int seed);

int randInt(int low, int high);

int randInt(int high);

// Returns all .log files in a given directory
std::vector<std::string> getLogFiles(const std::string &directory);

#endif // UTILS_HPP
