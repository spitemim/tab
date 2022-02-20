#include <stdio.h>
#include <stdlib.h>

void *
emalloc(size_t bytes)
{
    void *mem = malloc(bytes);

    if (!mem) {
        perror("emalloc failed");
        exit(1);
    }

    return mem;
}

void *
ecalloc(size_t num, size_t bytes)
{
    void *mem = calloc(num, bytes);

    if (!mem) {
        perror("ecalloc failed");
        exit(1);
    }

    return mem;
}

void *
erealloc(void *ptr, size_t bytes)
{
    void *mem = realloc(ptr, bytes);

    if (!mem) {
        perror("erealloc failed");
        exit(1);
    }

    return mem;
}
