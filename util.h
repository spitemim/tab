#ifndef UTIL_H__
#define UTIL_H__

/* Safe replacements for malloc, calloc, realloc */

void *emalloc(size_t bytes);

void *ecalloc(size_t num, size_t bytes);

void *erealloc(void *ptr, size_t bytes);

#endif
