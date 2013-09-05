#include <iostream>

#include "mpi.h"
#include "unistd.h"

#include "world.hpp"
#include "utils.hpp"

int main(int argc, char *argv[])
{
    int world_size = 10;
    int creature_count = 10;
    int obstacle_count = 10;
    int max_ticks = 10;
    int random_seed = 0;

    // Parse program arguments
    int option = 0;
    while ((option = getopt(argc, argv,"hs:c:t:r:o:")) != -1) {
        switch (option) {
        case 's':
            world_size = std::stoi(optarg);
            break;
        case 'c':
            creature_count = std::stoi(optarg);
            break;
        case 't':
            max_ticks = std::stoi(optarg);
            break;
        case 'r':
            random_seed = std::stoi(optarg);
            break;
        case 'o':
            obstacle_count = std::stoi(optarg);
            break;
        case 'h':
        default:
            std::cout << "usage: " << argv[0] << " [-h] [-r SEED] [-s WORLDSIZE] [-c CREAUTECOUNT] [-t MAXTICKS] [-o OBSTACLECOUNT]" << std::endl;
            return 1;
        }
    }

    initRandom(random_seed);

    // MPI stuff
    int rc = MPI_Init(&argc, &argv);
    if (rc != MPI_SUCCESS)
    {
        std::cerr << "Error starting MPI program. Terminating." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, rc);
    }

    // Get the number of processes
    int comm_size;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

    // Get the rank of the process
    int comm_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    std::cout << "Initializing world with size " << world_size << "x" << world_size << " and " << creature_count << " creatures." << std::endl;
    std::cout << "Simulation will run for " << max_ticks << " ticks." << std::endl;
    std::cout << "Using " << comm_size << " processes." << " Own rank is " << comm_rank << " on " << processor_name << std::endl;

    World world(world_size, world_size, comm_size, comm_rank, processor_name);

    world.populate(creature_count, obstacle_count);

    std::cout << "Starting simulation" << std::endl;
    world.simulate(max_ticks);
    std::cout << "Finished simulation" << std::endl;

    MPI_Finalize();
    return 0;
}
