#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "util.h"

#define  TABLE_INIT_SIZE 1024

typedef struct entry_ {
    char *key;
    char *value;
} entry;

typedef struct tab_ {
    unsigned int seed;
    int size;
    int numentries;

    entry **entries;
} tab;

static unsigned int
hash(char *key, int seed)
{
    int hash = seed;

    while (*key)
        hash += 31 * *key++;

    return hash;
}

/* Allocate an entry and return it */
static entry *
entrynew(char *key, char *value)
{
    entry *e = ecalloc(1, sizeof(entry));

    e->key = emalloc(strlen(key) + 1);
    e->value = emalloc(strlen(value) + 1);

    strcpy(e->key, key);
    strcpy(e->value, value);

    return e;
}

static void
entryfree(entry *e)
{
    if (e) {
        free(e->key);
        free(e->value);
        free(e);
    }
}

/* Will find an entry by key and return its index, or -1 if the
 * entry doesn't exist. */
static int
find(tab *table, char *key)
{
    unsigned int i, h;

    h = hash(key, table->seed) % table->size;

    for (i = h; i < table->size; ++i) {
        if (table->entries[i] &&
                !strcmp(table->entries[i]->key, key)) {
            return i;
        }
    }
    for (i = 0; i < h; ++i) {
        if (table->entries[i] &&
                !strcmp(table->entries[i]->key, key)) {
            return i;
        }
    }

    return -1;
}

/* Create a new table */
tab *
tabnew(unsigned int seed)
{
    tab *table = ecalloc(1, sizeof(tab));

    /* The table will grow as it fills up */
    table->size = TABLE_INIT_SIZE;

    table->seed = seed;

    table->entries = ecalloc(TABLE_INIT_SIZE, sizeof(entry *));

    return table;
}

/* Free all memory in a table */
void
tabfree(tab *table)
{
    if (table) {
        int i;

        for (i = 0; i < table->size; ++i) {
            entryfree(table->entries[i]);
        }

        free(table->entries);

        free(table);
    }
}

/* Set a value in the table */
void
tabset(tab *table, char *key, char *value)
{
    entry *e;
    int place = find(table, key);

    /* find() returns -1 if the entry doesn't exist */
    if (place == -1) {
        ++table->numentries;

        place = hash(key, table->seed) % table->size;

        if (table->entries[place]) {
            /* Something already exists here! Find the next
             * available slot. */
            while (table->entries[place]) ++place;
        }

        /* Create the new entry */
        table->entries[place] = entrynew(key, value);
    } else {
        /* Item exists, just update the value */
        e = table->entries[place];

        e->value = erealloc(e->value, strlen(value) + 1);
        strcpy(e->value, value);
    }

    /* If we reach 75% capacity, double the size of the table */
    if (table->numentries >= table->size * 0.75) {
        table->size *= 2;
        table->entries = erealloc(table->entries, sizeof(entry *) * table->size);
    }
}

/* Get a value in table */
char *
tabget(tab *table, char *key)
{
    int place;

    /* If the entry doesn't exist */
    if ((place = find(table, key)) == -1)
        return NULL;

    return table->entries[place]->value;
}

/* Delete a value from hashtable */
void
tabdel(tab *table, char *key)
{
    int place;

    /* If the entry doesn't exist */
    if ((place = find(table, key)) == -1) {
        printf("ERROR: '%s' doesn't exist, can't delete.\n", key);
        return;
    }

    entryfree(table->entries[place]);

    table->entries[place] = NULL;

    --table->numentries;
}

void
tabprint(tab *table)
{
    entry *e;
    int i;

    printf("Hashtable\n"
           " |- Size: %d\n"
           " |- Number of entries: %d\n"
           " |- Hash seed: %u\n |\n", table->size, table->numentries, table->seed);

    for (i = 0; i < table->size; ++i) {
        if ((e = table->entries[i])) {
            printf(" |-- (%d) '%s' : '%s'\n", i, e->key, e->value);
        }
    }
    puts(" \\_");
}
