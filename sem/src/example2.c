#include <stdio.h>
#include <time.h>

#include "diff.h"

#define RUNS 4000000000ULL
//#define CLOCK CLOCK_PROCESS_CPUTIME_ID
#define CLOCK CLOCK_MONOTONIC

struct Foo {
    char x;
    short y;
    int z;
};

struct Bar {
    char x;
    short y;
    int z;
} __attribute__((packed));

int main()
{
    struct Foo foo;
    struct Bar bar;

    struct timespec start;
    struct timespec end;
    struct timespec diff;

    printf("aligned size: %lu\n", sizeof(foo));
    printf("unaligned size: %lu\n", sizeof(bar));

    clock_gettime(CLOCK, &start);
    for (unsigned long long i = 0; i < RUNS; ++i)
    {
         foo.z = 1;
         foo.z += 1;
    }
    clock_gettime(CLOCK, &end);
    diff = ts_diff(start, end);
    printf("aligned runtime: %lli.%.9li s\n", (long long)diff.tv_sec, diff.tv_nsec);

    clock_gettime(CLOCK, &start);
    for (unsigned long long i = 0; i < RUNS; ++i)
    {
        bar.z = 1;
        bar.z += 1;
    }
    clock_gettime(CLOCK, &end);
    diff = ts_diff(start, end);
    printf("unaligned runtime: %lli.%.9li s\n", (long long)diff.tv_sec, diff.tv_nsec);

    return 0;
}
