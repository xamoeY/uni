/****************************************************************************/
/****************************************************************************/
/**                                                                        **/
/**                TU Muenchen - Institut fuer Informatik                  **/
/**                                                                        **/
/** Copyright: Prof. Dr. Thomas Ludwig                                     **/
/**            Andreas C. Schmidt                                          **/
/**            JK und andere  besseres Timing, FLOP Berechnung             **/
/**                                                                        **/
/** File:      partdiff-par.c                                              **/
/**                                                                        **/
/** Purpose:   Partial differential equation solver for Gauss-Seidel and   **/
/**            Jacobi method.                                              **/
/**                                                                        **/
/****************************************************************************/
/****************************************************************************/

/* ************************************************************************ */
/* Include standard header file.                                            */
/* ************************************************************************ */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <sys/time.h>
#include "partdiff-par.h"
#include <mpi.h>

struct calculation_arguments
{
    int     N;              /* adressable local memspace                      */
    int N_global;   /* global lineindex                   */
    int     num_matrices;   /* number of matrices                             */
    double  h;              /* length of a space between two lines            */
    double  ***Matrix;      /* index matrix used for addressing M             */
    double  *M;             /* two matrices with real values                  */
    int nproc;      /* number of processes                */
    int rank;       /* rank of operating process              */
    int offset;     /* global offset of process local lines           */
};

struct calculation_results
{
    int     m;
    int     stat_iteration; /* number of current iteration                    */
    double  stat_precision; /* actual precision of all slaves in iteration    */
};

/* ************************************************************************ */
/* Global variables                                                         */
/* ************************************************************************ */

/* time measurement variables */
struct timeval start_time;       /* time when program started                      */
struct timeval comp_time;        /* time when calculation completed                */


/* ************************************************************************ */
/* initVariables: Initializes some global variables                         */
/* ************************************************************************ */
static
void
initVariables (struct calculation_arguments* arguments, struct calculation_results* results, struct options const* options)
{
    MPI_Comm_size(MPI_COMM_WORLD, &arguments->nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &arguments->rank);
    int const nproc = arguments->nproc;
    int const rank = arguments->rank;
    int rest;
    
    arguments->N_global = (options->interlines * 8) + 9 - 1;
    rest = (arguments->N_global + 1 - 2) % nproc;

    if(rank < rest){
    arguments->offset = (((arguments->N_global + 1 - 2) / nproc) * rank) + rank;
    arguments->N = ((arguments->N_global + 1 - 2) / nproc) + 2 + 1 - 1;
    }
    else{
    arguments->offset = (((arguments->N_global + 1 - 2) / nproc) * rank) + rest;
    arguments->N = ((arguments->N_global + 1 - 2) / nproc) + 2 - 1;
    }   
    
    arguments->num_matrices = (options->method == METH_JACOBI) ? 2 : 1;
    arguments->h = 1.0 / arguments->N_global;

    results->m = 0;
    results->stat_iteration = 0;
    results->stat_precision = 0;
}

/* ************************************************************************ */
/* freeMatrices: frees memory for matrices                                  */
/* ************************************************************************ */
static
void
freeMatrices (struct calculation_arguments* arguments)
{
    int i;

    for (i = 0; i < arguments->num_matrices; i++)
    {
        free(arguments->Matrix[i]);
    }

    free(arguments->Matrix);
    free(arguments->M);
}

/* ************************************************************************ */
/* allocateMemory ()                                                        */
/* allocates memory and quits if there was a memory allocation problem      */
/* ************************************************************************ */
static
void*
allocateMemory (size_t size)
{
    void *p;

    if ((p = malloc(size)) == NULL)
    {
        printf("\n\nSpeicherprobleme!\n");
        /* exit program */
        exit(1);
    }

    return p;
}

/* ************************************************************************ */
/* allocateMatrices: allocates memory for matrices                          */
/* ************************************************************************ */
static
void
allocateMatrices (struct calculation_arguments* arguments)
{
    int m, i;

    int const N = arguments->N;
    int const N_global = arguments->N_global;

    arguments->M = allocateMemory(arguments->num_matrices * (N + 1) * (N_global + 1) * sizeof(double));
    arguments->Matrix = allocateMemory(arguments->num_matrices * sizeof(double**));

    for (m = 0; m < arguments->num_matrices; m++)
    {
        arguments->Matrix[m] = allocateMemory((N + 1) * sizeof(double*));

        for (i = 0; i < N + 1; i++)
        {
            arguments->Matrix[m][i] = arguments->M + (m * (N + 1) * (N_global + 1)) + (i * (N_global + 1));
        }
    }
}

/* ************************************************************************ */
/* initMatrices: Initialize matrix/matrices and some global variables       */
/* ************************************************************************ */
static
void
initMatrices (struct calculation_arguments* arguments, struct options const* options)
{
    int g, i, j;                                /*  local variables for loops   */

    int const N = arguments->N;
    int const N_global = arguments->N_global;
    int const offset = arguments->offset;
    int const rank = arguments->rank;
    int const nproc = arguments->nproc;
    double const h = arguments->h;
    double*** Matrix = arguments->Matrix;

    /* initialize matrix/matrices with zeros */
    for (g = 0; g < arguments->num_matrices; g++)
    {
        for (i = 0; i < N + 1; i++)
        {
            for (j = 0; j < N_global + 1; j++)
            {
                Matrix[g][i][j] = 0.0;
            }
        }
    }

    /* initialize borders, depending on function (function 2: nothing to do) */
    if (options->inf_func == FUNC_F0)
    {
        for (g = 0; g < arguments->num_matrices; g++)
        {
            for (i = 0; i < N + 1; i++)
            {
                Matrix[g][i][0] = 1.0 - (h * (i + offset));
                Matrix[g][i][N_global] = h * (i + offset);
            }
        }
        
        if(rank == 0)
        for (g = 0; g < arguments->num_matrices; g++)
            for (i = 0; i < N_global + 1; i++)
                Matrix[g][0][i] = 1.0 - (h * i);
        
        if(rank == nproc - 1)
        for (g = 0; g < arguments->num_matrices; g++)
            for (i = 0; i < N_global + 1; i++)
                Matrix[g][N][i] = h * i;

        for (g = 0; g < arguments->num_matrices; g++)
        {
            Matrix[g][N][0] = 0.0;
            Matrix[g][0][N_global] = 0.0;
        }
    }
}

/* ************************************************************************ */
/* calculate: solves the equation                                           */
/* ************************************************************************ */
static
void
calculate (struct calculation_arguments const* arguments, struct calculation_results *results, struct options* options)
{
    int i, j;                                   /* local variables for loops  */
    int m1, m2;                                 /* used as indices for old and new matrices       */
    double star;                                /* four times center value minus 4 neigh.b values */
    double residuum;                            /* residuum of current iteration                  */
    double maxresiduum;                         /* maximum residuum value of a slave in iteration */
    double maxresiduumbuf;                      /* holds the preceeding maxresiduum               */
    int termflag;                               /* once the last rank is accurate enough to 
                                                   terminate by precision, it communicates
                                                   this information using this flag to the
                                                   next process above it.                           */
    int termflag2;                              /* this flag is set and sent down starting from
                                                   rank 0 once rank 0 receives termflag = 1 from a
                                                   process beneath it                               */

    int const N = arguments->N;
    int const N_global = arguments->N_global;
    double const h = arguments->h;
    int const nproc = arguments->nproc;
    int const rank = arguments->rank; 

    int term_iteration = options->term_iteration;
    termflag = 0;
    termflag2 = 0;
    
    /* initialize m1 and m2 depending on algorithm */
    if (options->method == METH_JACOBI)
    {
        m1 = 0;
        m2 = 1;
    }
    else
    {
        m1 = 0;
        m2 = 0;
    }
    
    while (term_iteration > 0)
    {
        double** Matrix_Out = arguments->Matrix[m1];
        double** Matrix_In  = arguments->Matrix[m2];

        maxresiduum = 0;
        maxresiduumbuf = 0;
        
        if(rank > 0){
            // receive communication line from above
            MPI_Recv(Matrix_Out[0], N_global + 1, MPI_DOUBLE, rank - 1,
                    rank - 1 + results->stat_iteration, MPI_COMM_WORLD, NULL);

            // receive preceeding maxresiduum
            MPI_Recv(&maxresiduumbuf, 1, MPI_DOUBLE, rank - 1, rank - 1, MPI_COMM_WORLD, NULL);

            // receive final termination flag from above
            MPI_Recv(&termflag2, 1, MPI_DOUBLE, rank - 1, rank - 1, MPI_COMM_WORLD, NULL); 
            }

        // in the initial run the first process must not receive values
        if(results->stat_iteration > 0) 
            if(rank != nproc - 1){
                // reveive communication line from below
                MPI_Recv(Matrix_Out[N], N_global + 1, MPI_DOUBLE, rank + 1, 
                        rank + 1 + results->stat_iteration - 1, MPI_COMM_WORLD, NULL);

                // receive preliminary termflag from preceeding rank
                MPI_Recv(&termflag, 1, MPI_INT, rank + 1, rank + 1, MPI_COMM_WORLD, NULL);
            }

        /* over all rows */
        for (i = 1; i < N; i++)
        {
            /* over all columns */
            for (j = 1; j < N_global; j++)
            {
                star = 0.25 * (Matrix_In[i-1][j] +
                        Matrix_In[i][j-1] + 
                        Matrix_In[i][j+1] + 
                        Matrix_In[i+1][j]);

                if (options->inf_func == FUNC_FPISIN)
                {
                    star += (0.25 * TWO_PI_SQUARE * h * h) * 
                        sin((PI * h) * ((double)i + arguments->offset)) *
                        sin((PI * h) * (double)j);
                }

                if (options->termination == TERM_PREC || term_iteration == 1)
                {
                    residuum = Matrix_In[i][j] - star;
                    residuum = (residuum < 0) ? -residuum : residuum;
                    maxresiduum = (residuum < maxresiduum) ? maxresiduum : residuum;
                    maxresiduum = (maxresiduumbuf < maxresiduum) ? maxresiduum : maxresiduumbuf;
                }

                Matrix_Out[i][j] = star;
            }
        }

        // in the last iteration the values must not get sent upwards, this lets the pipeline run out
        if(term_iteration > 1)
        if(rank > 0){
            // send communication line upwards
            MPI_Send(Matrix_Out[1], N_global + 1, MPI_DOUBLE, rank - 1,
                    rank + results->stat_iteration, MPI_COMM_WORLD);

            // send prelimary termination flag upwards
            MPI_Send(&termflag, 1, MPI_INT, rank - 1, rank, MPI_COMM_WORLD);
        }

        if(rank != nproc - 1){
            // send communication line downwards
            MPI_Send(Matrix_Out[N - 1], N_global + 1, MPI_DOUBLE, rank + 1, 
                    rank + results->stat_iteration, MPI_COMM_WORLD);

            // send maxresiduum down the procs
            MPI_Send(&maxresiduum, 1, MPI_DOUBLE, rank + 1, rank, MPI_COMM_WORLD);

            // send final termflag downwards
            MPI_Send(&termflag2, 1, MPI_DOUBLE, rank + 1, rank, MPI_COMM_WORLD);
        }

        /* exchange m1 and m2 */
        i = m1;
        m1 = m2;
        m2 = i;

        results->stat_iteration++;
        results->stat_precision = maxresiduum;

        if(termflag2 == 1)
            term_iteration = 0;

        if(rank == 0)
            if(termflag == 1)
            {
                termflag2 = 1;
            }

        /* check for stopping calculation, depending on termination method */
        if (options->termination == TERM_PREC){
            if (rank == nproc - 1) {
                if (maxresiduum < options->term_precision && termflag != -1)
                {
                    termflag = 1;
                }
            }
        }
        else if (options->termination == TERM_ITER)
        {
            term_iteration--;
        }
    }

    results->m = m2;
}

/* ************************************************************************ */
/*  displayStatistics: displays some statistics about the calculation       */
/* ************************************************************************ */
static
    void
displayStatistics (struct calculation_arguments const* arguments, struct calculation_results const* results, struct options const* options)
{
    const int N = arguments->N;
    const int N_global = arguments->N_global;
    const int nproc = arguments->nproc;

    double time = (comp_time.tv_sec - start_time.tv_sec) + (comp_time.tv_usec - start_time.tv_usec) * 1e-6;
    printf("Berechnungszeit:    %f s \n", time);

    //Calculate Flops
    // star op = 5 ASM ops (+1 XOR) with -O3, matrix korrektur = 1
    double q = 6;
    double mflops;
    long dataPoints = (long) (N - 1) * (N_global - 1) * results->stat_iteration;

    if (options->inf_func == FUNC_F0)
    {
        // residuum: checked 1 flop in ASM, verified on Nehalem architecture.
        q += 1.0;
    }
    else
    {
        // residuum: 11 with O0, but 10 with "gcc -O3", without counting sin & cos
        q += 10.0;
    }

    /* calculate flops  */
    mflops = (q * dataPoints) * 1e-6;
    printf("Executed float ops: %f MFlop\n", mflops);

    printf("Speed:              %f MFlop/s\n", mflops / time);

    printf("Memory footprint:   %f MiB\n", nproc * (N + 1) * (N_global + 1) * sizeof(double) * arguments->num_matrices / 1024.0 / 1024.0);
    printf("Mem thp (read):     %f MiB/s\n", dataPoints * 4.0 / 1024 / 1024 / time);
    printf("Mem thp (write):    %f MiB/s\n", dataPoints * 1.0 / 1024 / 1024 / time);
    printf("Mem thp (total):    %f MiB/s\n", dataPoints * 5.0 / 1024 / 1024 / time);

    printf("Berechnungsmethode: ");

    if (options->method == METH_GAUSS_SEIDEL)
    {
        printf("Gauss-Seidel");
    }
    else if (options->method == METH_JACOBI)
    {
        printf("Jacobi");
    }

    printf("\n");
    printf("Interlines:         %d\n",options->interlines);
    printf("Stoerfunktion:      ");

    if (options->inf_func == FUNC_F0)
    {
        printf("f(x,y)=0");
    }
    else if (options->inf_func == FUNC_FPISIN)
    {
        printf("f(x,y)=2pi^2*sin(pi*x)sin(pi*y)");
    }

    printf("\n");
    printf("Terminierung:       ");

    if (options->termination == TERM_PREC)
    {
        printf("Hinreichende Genaugkeit");
    }
    else if (options->termination == TERM_ITER)
    {
        printf("Anzahl der Iterationen");
    }

    printf("\n");
    printf("Anzahl Iterationen: %d\n", results->stat_iteration);
    printf("Norm des Fehlers:   %e\n", results->stat_precision);
}

// Debug function for pretty printing matrix
// Use DEBUG = 1 and 0 interlines to have a look.
__attribute__((cold))
    void
    printDebug(struct calculation_arguments const* arguments, struct calculation_results const* results) {
        const int mpi_nproc = arguments->nproc;
        const int mpi_myrank = arguments->rank;
        const int N = arguments->N;
        const int N_global = arguments->N_global;
        const int BUF = 1000;
        char* output = malloc(BUF * sizeof(char));
        int length = 0;
        char* recv_buf = malloc(BUF * sizeof(char) * mpi_nproc);

        length += snprintf(output + length, BUF - length, "\nrank %d matrix:\n", mpi_myrank);
        length += snprintf(output + length, BUF - length, "         ");

        for (int j = 0; j < N_global; ++j)
        {
            length += snprintf(output + length, BUF - length, "%5s %d", "col", j);
        }
        length += snprintf(output + length, BUF - length, "\n          ");
        for (int j = 0; j < N_global; ++j)
        {
            length += snprintf(output + length, BUF - length, "-------");
        }
        length += snprintf(output + length, BUF - length, "\n");
        for (int i = 0; i < N + 1; ++i)
        {
            length += snprintf(output + length, BUF - length, "line %2d | ", i);
            for (int j = 0; j < N_global + 1; ++j)
            {
                length += snprintf(output + length, BUF - length, "%7.4f", arguments->Matrix[results->m][i][j]);
            }
            if (i == 0 || i == N)
                length += snprintf(output + length, BUF - length, " <- comm line");
            length += snprintf(output + length, BUF - length, "\n");
        }

        length += snprintf(output + length, BUF - length, "\n");
        MPI_Gather(output, BUF, MPI_CHAR, recv_buf, BUF, MPI_CHAR, 0, MPI_COMM_WORLD);
        for(int i = 0; i < mpi_nproc; ++i)
            printf("%s", recv_buf + BUF * i);
        fflush(stdout);

        free(output);
        free(recv_buf);
    }

/* ************************************************************************ */
/*  main                                                                    */
/* ************************************************************************ */
    int
main (int argc, char** argv)
{
    MPI_Init(&argc, &argv);

    struct options options;
    struct calculation_arguments arguments;
    struct calculation_results results;

    /* get parameters */
    AskParams(&options, argc, argv);

    initVariables(&arguments, &results, &options);

    allocateMatrices(&arguments);        /*  get and initialize variables and matrices  */
    initMatrices(&arguments, &options);

    gettimeofday(&start_time, NULL);                  /*  start timer         */
    calculate(&arguments, &results, &options);        /*  solve the equation  */
    MPI_Barrier(MPI_COMM_WORLD);
    gettimeofday(&comp_time, NULL);                   /*  stop timer          */

   // printDebug(&arguments, &results); // pretty-print matrix if we are debugging
    if(arguments.rank == 0)
        displayStatistics(&arguments, &results, &options);
    DisplayMatrix("Matrix:", arguments.Matrix[results.m][0], options.interlines,
            arguments.rank, arguments.nproc, arguments.offset + ((arguments.rank > 0) ? 1 : 0), (arguments.offset + arguments.N - ((arguments.rank != arguments.nproc - 1) ? 1 : 0)));

    freeMatrices(&arguments);                                       /*  free memory     */

    MPI_Finalize();

    return 0;
}
