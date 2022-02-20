#ifndef TAB_H__
#define TAB_H__

/* Hash table structure */
typedef struct tab_ tab;

/* Create a new table */
tab *tabnew(unsigned int seed);

/* Free all memory in a table */
void tabfree(tab *table);

/* Set a value in the table */
void tabset(tab *table, char *key, char *value);

/* Get a value from table */
char *tabget(tab *table, char *key);

/* Delete a value from hashtable */
void tabdel(tab *table, char *key);

/* Print the contents of a hashtable (for debugging */
void tabprint(tab *table);

#endif
