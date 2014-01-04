#include <stdio.h>
#include <time.h>

#include "diff.h"

#define RUNS 4000000000ULL
//#define CLOCK CLOCK_PROCESS_CPUTIME_ID
#define CLOCK CLOCK_MONOTONIC

int x;
long long y;

int main()
{
    struct timespec start;
    struct timespec end;
    struct timespec diff;

    printf("int: %lu\n", sizeof(x));
    printf("long long: %lu\n", sizeof(y));

    clock_gettime(CLOCK, &start);
    for (unsigned long long i = 0; i < RUNS; ++i)
    {
         x = 1;
         x += 1;
    }
    clock_gettime(CLOCK, &end);
    diff = ts_diff(start, end);
    printf("int runtime: %lli.%.9li s\n", (long long)diff.tv_sec, diff.tv_nsec);

    clock_gettime(CLOCK, &start);
    for (unsigned long long i = 0; i < RUNS; ++i)
    {
         y = 1;
         y += 1;
    }
    clock_gettime(CLOCK, &end);
    diff = ts_diff(start, end);
    printf("long runtime: %lli.%.9li s\n", (long long)diff.tv_sec, diff.tv_nsec);

    return 0;
}
