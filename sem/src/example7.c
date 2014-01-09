#include <stdio.h>
#include <stdlib.h>

#define SIZE 1024 * 1024
#define ALIGN 4096
int main()
{
    void* a = malloc(SIZE);
    void* b = aligned_alloc(ALIGN, SIZE);
    
    printf("a: %p, a %% %i: %lu\n", a, ALIGN, ((unsigned long)a) % ALIGN);
    printf("b: %p, b %% %i: %lu\n", b, ALIGN, ((unsigned long)b) % ALIGN);
    return 0;
}
