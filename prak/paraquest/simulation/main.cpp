#include <iostream>

#include "mpi.h"
#include "unistd.h"

#include "world.hpp"
#include "utils.hpp"

int main(int argc, char *argv[])
{
    int world_size = 100;
    int creature_count = 10;
    int simulation_length = 10;
    int random_seed = 0;

    // Parse program arguments
    int option = 0;
    while ((option = getopt(argc, argv,"hs:c:l:r:")) != -1) {
        switch (option) {
        case 's':
            world_size = std::stoi(optarg);
            break;
        case 'c':
            creature_count = std::stoi(optarg);
            break;
        case 'l':
            simulation_length = std::stoi(optarg);
            break;
        case 'r':
            random_seed = std::stoi(optarg);
            break;
        case 'h':
        default:
            std::cout << "usage: " << argv[0] << " [-h] [-s WORLDSIZE] [-c CREAUTECOUNT] [-l SIMULATIONLENTH]" << std::endl;
            return 1;
        }
    }

    initRandom(random_seed);

    World world(world_size, world_size);

    world.populate(creature_count);
    world.simulate(simulation_length);

    return 0;
}
