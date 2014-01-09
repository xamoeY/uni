#include <stdio.h>

struct Foo {
    char x;
    __uint128_t z;
    char a;
    __uint128_t b;
};

int main()
{
    struct Foo lol;
    printf("%lu\n", sizeof(lol));
    return 0;
}
