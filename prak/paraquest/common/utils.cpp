#include "utils.hpp"

#include <algorithm>
#include <iostream>

#include "dirent.h"

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

std::vector<std::string> getLogFiles(const std::string &directory)
{
    std::vector<std::string> files;

    DIR *dir = opendir(directory.c_str());

    struct dirent *dir_item = NULL;

    if(dir != NULL)
    {
        while((dir_item = readdir(dir)))
        {
            std::string file(dir_item->d_name);
            if(file.rfind(".log") != file.npos)
                files.push_back(dir_item->d_name);
        }

        closedir(dir);
    }
    else
    {
        std::cerr << "Unable to open specified directory." << std::endl;
    }

    std::sort(files.begin(), files.end());
    return files;
}
