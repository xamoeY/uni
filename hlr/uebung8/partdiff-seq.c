/****************************************************************************/
/****************************************************************************/
/**                                                                        **/
/**                TU Muenchen - Institut fuer Informatik                  **/
/**                                                                        **/
/** Copyright: Prof. Dr. Thomas Ludwig                                     **/
/**            Andreas C. Schmidt                                          **/
/**            JK und andere  besseres Timing, FLOP Berechnung             **/
/**                                                                        **/
/** File:      partdiff-seq.c                                              **/
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
#include "partdiff-seq.h"
#define plus + 1

struct calculation_arguments
{
    int     N;              /* number of spaces between lines for this process*/
    int     N_global;       /* global number of lines                         */
    int     starting_offset;/* global starting offset of this process         */
    int     num_matrices;   /* number of matrices                             */
    double  h;              /* length of a space between two lines            */
    double  ***Matrix;      /* index matrix used for addressing M             */
    double  *M;             /* two matrices with real values                  */
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
    // Get general MPI context info
    int mpi_nproc;
    MPI_Comm_size(MPI_COMM_WORLD, &mpi_nproc);

    int mpi_myrank;
    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_myrank);

    // Figure out rest before we split so we can properly handle corner cases where matrix lines doesn't match process count cleanly
    arguments->N_global = (options->interlines * 8) + 9 - 1;
    int rest = arguments->N_global % mpi_nproc;

    // Split number of total lines in matrix by number of MPI processes we have available
    arguments->N = arguments->N_global / mpi_nproc;

    arguments->starting_offset = arguments->N * mpi_myrank;

    // If the splits don't divide cleanly, make the lower processes calculate one more line each
    if (mpi_myrank < rest)
    {
        arguments->starting_offset += mpi_myrank;
        arguments->N += 1;
    }
    else
    {
        arguments->starting_offset += rest;
    }

    printf("I am rank %d, matrix has %d lines total, I have %d lines, my global start/offset is %d, my rest is %d\n", mpi_myrank, arguments->N_global, arguments->N, arguments->starting_offset, rest);

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
    int i, m;

    int const N = arguments->N plus;
    int const N_global = arguments->N_global;

    arguments->M = allocateMemory(arguments->num_matrices * (N + 1) * (N_global + 1) * sizeof(double));
    arguments->Matrix = allocateMemory(arguments->num_matrices * sizeof(double**));

    for (m = 0; m < arguments->num_matrices; m++)
    {
        arguments->Matrix[m] = allocateMemory((N + 1) * sizeof(double*));

        for (i = 0; i <= N; i++)
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
    int const offset = arguments->starting_offset;
    double const h = arguments->h;
    double*** Matrix = arguments->Matrix;

    // Get general MPI context info
    int mpi_nproc;
    MPI_Comm_size(MPI_COMM_WORLD, &mpi_nproc);

    int mpi_myrank;
    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_myrank);

    /* initialize matrix/matrices with zeros */
    for (g = 0; g < arguments->num_matrices; g++)
    {
        for (i = 0; i <= N; i++)
        {
            for (j = 0; j <= N_global; j++)
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
            // Precalculate top line
            // Only in rank 0
            if(mpi_myrank == 0)
            {
                for (i = 0; i <= N_global; i++)
                {
                    Matrix[g][0][i] = 1.0 - (h * i);
                }
            }

            // Precalculate bottom line
            // Only in last rank
            if(mpi_myrank == mpi_nproc - 1)
            {
                for (i = 0; i <= N_global; i++)
                {
                    Matrix[g][N plus][i] = h * i;
                }
            }

            // Precalculate left and right columns
            if(mpi_myrank == 0)
            {
                for (i = 0; i <= N; i++)
                {
                    Matrix[g][i][0] = 1.0 - (h * (i + offset));
                    Matrix[g][i][N_global] = h * (i + offset);
                }
            }
            else
            {
                for (i = 0; i <= N; i++)
                {
                    Matrix[g][i plus][0] = 1.0 - (h * (i + offset));
                    Matrix[g][i plus][N_global] = h * (i + offset);
                }
            }
        }

        // Set top right to be 0
        // Only in rank 0
        if(mpi_myrank == 0)
        {
            for (g = 0; g < arguments->num_matrices; g++)
            {
                Matrix[g][0][N_global] = 0;
            }
        }

        // Set bottom left to be 0
        // Only in last rank
        if(mpi_myrank == mpi_nproc - 1)
        {
            for (g = 0; g < arguments->num_matrices; g++)
            {
                Matrix[g][N plus][0] = 0;
            }
        }
        
        // TODO OMG
        // fuck around with matrix
        if(mpi_myrank == 100)
        {
            for (g = 0; g < arguments->num_matrices; g++)
            {
                for (i = 0; i <= N plus; i++)
                {
                    for (j = 0; j <= N_global; j++)
                    {
                        Matrix[g][i][j] = 0.111;
                    }
                }
            }
        }
    }
}

/* ************************************************************************ */
/* calculate: solves the equation                                           */
/* ************************************************************************ */
static
    void
calculate (struct calculation_arguments const* arguments, struct calculation_results *results, struct options const* options)
{
    int i, j;                                   /* local variables for loops  */
    int m1, m2;                                 /* used as indices for old and new matrices       */
    double star;                                /* four times center value minus 4 neigh.b values */
    double residuum;                            /* residuum of current iteration                  */
    double maxresiduum;                         /* maximum residuum value of a slave in iteration */

    int const N = arguments->N;
    int const N_global = arguments->N_global;
    double const h = arguments->h;

    int term_iteration = options->term_iteration;

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

        /* over all rows */
        for (i = 1; i < N plus; i++)
        {
            /* over all columns */
            for (j = 1; j < N_global; j++)
            {
                star = 0.25 * (Matrix_In[i-1][j] + Matrix_In[i][j-1] + Matrix_In[i][j+1] + Matrix_In[i+1][j]);

                if (options->inf_func == FUNC_FPISIN)
                {
                    star += (0.25 * TWO_PI_SQUARE * h * h) * sin((PI * h) * (double)i) * sin((PI * h) * (double)j);
                }

                if (options->termination == TERM_PREC || term_iteration == 1)
                {
                    residuum = Matrix_In[i][j] - star;
                    residuum = (residuum < 0) ? -residuum : residuum;
                    maxresiduum = (residuum < maxresiduum) ? maxresiduum : residuum;
                }

                Matrix_Out[i][j] = star;
            }
        }

        results->stat_iteration++;
        results->stat_precision = maxresiduum;

        /* exchange m1 and m2 */
        i = m1;
        m1 = m2;
        m2 = i;

        /* check for stopping calculation, depending on termination method */
        if (options->termination == TERM_PREC)
        {
            if (maxresiduum < options->term_precision)
            {
                term_iteration = 0;
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
    int N = arguments->N;

    double time = (comp_time.tv_sec - start_time.tv_sec) + (comp_time.tv_usec - start_time.tv_usec) * 1e-6;
    printf("Berechnungszeit:    %f s \n", time);

    //Calculate Flops
    // star op = 5 ASM ops (+1 XOR) with -O3, matrix korrektur = 1
    double q = 6;
    double mflops;
    long dataPoints = (long) (N - 1) * (N - 1) * results->stat_iteration;

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

    printf("Memory footprint:   %f MiB\n",   (N + 1) * (N + 1) * sizeof(double) * arguments->num_matrices / 1024.0 / 1024.0);
    printf("Mem thp (read):     %f MiB/s\n", dataPoints * 4.0 / 1024 / 1024  / time);
    printf("Mem thp (write):    %f MiB/s\n", dataPoints * 1.0 / 1024 / 1024 / time);
    printf("Mem thp (total):    %f MiB/s\n", dataPoints * 5.0 / 1024 / 1024  / time);

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

/* ************************************************************************ */
/*  main                                                                    */
/* ************************************************************************ */
    int
main (int argc, char** argv)
{
    MPI_Init(&argc, &argv);

    // Get general MPI context info
    int mpi_nproc;
    MPI_Comm_size(MPI_COMM_WORLD, &mpi_nproc);

    int mpi_myrank;
    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_myrank);

    struct options options;
    struct calculation_arguments arguments;
    struct calculation_results results;

    /* get parameters */
    AskParams(&options, argc, argv);              /* ************************* */

    initVariables(&arguments, &results, &options);           /* ******************************************* */

    allocateMatrices(&arguments);        /*  get and initialize variables and matrices  */
    initMatrices(&arguments, &options);            /* ******************************************* */

    gettimeofday(&start_time, NULL);                   /*  start timer         */
    calculate(&arguments, &results, &options);                                      /*  solve the equation  */
    gettimeofday(&comp_time, NULL);                   /*  stop timer          */

    //printf("rank %d matrix: %f\n", mpi_myrank, arguments.Matrix[results.m][0][1]);
    //printf("rank %d matrix: %f\n", mpi_myrank, arguments.Matrix[results.m][4][1]);
    //displayStatistics(&arguments, &results, &options);                                  /* **************** */
    // TODO arguments.starting_offset + 1 weil wir die comm zeilen noch nichts haben?
    DisplayMatrix("Matrix:",                              /*  display some    */
            arguments.Matrix[results.m][0], options.interlines,
            mpi_myrank, mpi_nproc, arguments.starting_offset, arguments.starting_offset + arguments.N); /*  statistics and  */

    freeMatrices(&arguments);                                       /*  free memory     */

    MPI_Finalize();

    return 0;
}
