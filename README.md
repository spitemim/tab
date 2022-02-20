# tab - A simple hash table

## Description

**tab** is a simple hash table library for string key-value pairs.

```c
tab *mytable = tabnew(rand());

tabset(mytable, "this is a key", "this is a value");

puts(tabget(mytable, "this is a key")); /* "this is a value" */

tabdel(mytable, "this is a key"); /* :o it's gone! */

tabfree(mytable);
```

## Functions

A list of functions and their descriptions can be found in [tab.h](tab.h). Here's a quick overview:

```c
tab *tabnew(unsigned int seed);
```
Create a hash table structure. You need to supply a (preferably) random number to seed the hash function.

```c
void tabfree(tab *table);
```
Free all memory in a hash table.

```c
void tabset(tab *table, char *key, char *value);
```
Set the value of a key in the specified table. If the key doesn't exist in the table yet, it is created.

```c
char *tabget(tab *table, char *key);
```
Get the value of a key from the table, or NULL if it doesn't exist yet.

```c
void tabdel(tab *table, char *key);
```
Delete an entry from the table.


```c
void tabprint(tab *table);
```
Print the contents of the hashtable.

## License

This project is licensed under the GNU GPLv3. See the [license file](LICENSE).
