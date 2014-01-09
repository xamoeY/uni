#include <stdio.h>

__attribute__((force_align_arg_pointer))
void foo() {
    struct Lol {} lol;
}

int main()
{
    foo();
    return 0;
}
