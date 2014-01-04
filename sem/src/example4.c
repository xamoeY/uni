#include <stdio.h>

struct Foo {
    char x;
    double y;
    char z;
};

int main()
{
    struct Foo lol;
    printf("%lu\n", sizeof(lol));
    return 0;
}
