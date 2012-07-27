# NP Library

A utility c library demonstrating various data structures and algorithms.

## Building

     $ make

A successful compilation results in a dynamically linked library located at
`src/libnplib.so`.

## Testing

     $ make check

Builds `src/libnplib.so` then builds and runs a C-Unit based test program in
`test/np-lib-test`.

## Data Structures

### np_linkedlist

np_linkedlist is a singly linked list. The source is located:

     src/np_linkedlist.h
     src/np_linkedlist.c

See `test/np_linkedlist_test.c` for sample usage.

### np_arraylist

np_arraylist is a dynamic array. The source is located:

     src/np_arraylist.h
     src/np_arraylist.c

See `test/np_arraylist_test.c` for sample usage.

### np_hashmap

np_hashmap implements a hash based map (hashtable). Hash collisions are
resolved with chaining. The source is located:

     src/np_hashmap.h
     src/np_hashmap.c

See `test/np_hashmap_test.c` for sample usage.

### np_treemap

np_treemap is a red-black tree based sorted map. The map provides ordering
on the keys based upon a given comparator function. The source is located:

     src/np_treemap.h
     src/np_treemap.c

See `test/np_treemap_test.c` for sample usage.
