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

### np_dict

np_dict is a simple dictionary (hashtable). Hash collisions are resolved
with chaining. The dictionary source is contained in:

     src/np_dict.h
     src/np_dict.c

See `test/np_dict_test.c` for sample usage.


