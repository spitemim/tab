# tab - A simple hash table

## Description

**tab** is a simple hash table implementation for string key-value pairs.

## Functions

A list of functions and their descriptions can be found in [tab.h](tab.h). Here's a quick overview:

`tab *tabnew(unsigned int seed)`: Create a hash table struct. You need to supply a (preferably) random number to seed the hash function.

```
tab *tabnew(unsigned int seed)
```
