/*
Copyright 2022 spitemim

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
