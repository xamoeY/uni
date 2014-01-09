#include <stdio.h>

struct Foo {
    double a;
    char b;
    char c;
    short d;
    int e;
    double f;
};

int main()
{
    struct Foo lol;
    printf("%lu\n", sizeof(lol));
    return 0;
}
