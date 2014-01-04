#include <stdio.h>

struct Foo {
    char x;
    short y;
    int z;
};

int main()
{
    struct Foo lol;
    printf("%lu\n", sizeof(lol));
    return 0;
}
