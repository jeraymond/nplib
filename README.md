# NP Library

A utility C library of various data structures and algorithms.

## Building

     $ make

A successful compilation results in a dynamically linked library located at
`src/libnplib.so`.

Note: Use `gmake` on FreeBSD

## Testing

     $ make check

Builds `src/libnplib.so` then builds and runs a C-Unit based test program in
`test/np-lib-test`.

Note: Use `gmake` on FreeBSD

### Test Dependencies

The tests use CUnit. Ensure you have CUnit installed.

On Linux (Ubuntu): `apt-get install libcunit1 libcunit1-dev`

On FreeBSD: `pkd_add -r cunit`

On OS X

1. Download Cunit: http://sourceforge.net/projects/cunit/files/CUnit/2.1-2/
2. Extract it
3. Configure and install it

```bash
./configure
make
make install
```

## Data Structures

### Singly Linked List

The singly [linked list][1] implementation `np_linkedlist` is found at:

     src/np_linkedlist.h
     src/np_linkedlist.c

[1]: http://en.wikipedia.org/wiki/Linked_list

#### Operations

* __push__ - add an item to the front of the list
* __pop__ - remove the first item in the list
* __reverse__ - reverse order of items in the list
* __length__ - determine the length of the list
* __add__ - add an item at a particular location in the list
* __remove__ - remove an item at a particular location in the list
* __get__ - get an item at a particular location in the list
* __iterator__ - an iterator to iterate over items in the list

See `test/np_linkedlist_test.c` for sample usage.

#### Performance

Push and pop operate at the head of the list in constant O(1) time. Add,
remove, and get operate in _search time_ + O(1) time. Searching for an item
by index is a O(i) operation where i is target index. Length and reverse
operate in O(n) linear time. The entire list is traversed to determine its
length or to reverse the list.

The extra space required by the list is linear O(n) relative to the size of
the list.

### Array List

The array list (or [dynamic array][2]) implementation `np_arraylist` is found
at:

     src/np_arraylist.h
     src/np_arraylist.c

[2]:http://en.wikipedia.org/wiki/Dynamic_array

#### Operations

* __push__ - add an item to the front of the list
* __pop__ - remove the first item in the list
* __reverse__ - reverses the order of items in the list
* __length__ - determine the length of the list
* __add__ - add an item at a particular location in the list
* __remove__ - remove an item at a particular location from the list
* __get__ - get an item at a particular location in the list
* __iterator__ - an iterator to iterate over items in the list

See `test/np_arraylist_test.c` for sample usage.

#### Performance

Push and pop operate at the head of the list in linear O(n) time. Inserting
or removing list items requires moving all items after the target item in
the list. Add and remove operate generally at linear O(n) time. Adding or
removing at the end of the list is constant O(n) time (amoritized). Get and
length operate in constant O(1) time. Reverse operates in linear O(n) time.

The extra space required by the list is linear O(n) relative to the size
of the list.

### Hash Map

The hash map (or [hash table][3]) implementation `np_hashmap` is found at:

     src/np_hashmap.h
     src/np_hashmap.c

[3]:http://en.wikipedia.org/wiki/Hash_table

#### Operations

* __put__ - associates the given value with the specified key
* __get__ - gets the item associated with the given key
* __remove__ - removes the given key and its assocated value

See `test/np_hashmap_test.c` for sample usage.

#### Performance

Insert and get operate on average in O(1 + n/k) time and linear O(n) time
in the worst case. Put is constant O(1) in time.

The extra space required by the map is linear O(n) relative to the number
of items in the map.

### Tree Map

The tree map implementation `np_treemap` is found at:

     src/np_treemap.h
     src/np_treemap.c

#### Operations

* __put__ - associates the given value with the specified key
* __get__ - gets the item associated with the given key
* __remove__ - removes the given key and its assocated value
* __iterator__ - iterate over map keys in key order

See `test/np_treemap_test.c` for sample usage.

#### Performance

Put, get, and remove operate in logarithmic O(log n) time.

The extra space required by the map is linear O(n) relative to the number
of items in the map.
