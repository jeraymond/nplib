LIB = libnplib.so
INC = np_hashmap.h np_treemap.h np_linkedlist.h np_arraylist.h
SRC = np_hashmap.c np_treemap.c np_linkedlist.c np_arraylist.c
CCFLAGS = -std=c99 -pedantic -Wall -W -g -O2
LIBFLAGS = -fpic -c

all: $(LIB)

$(LIB): $(SRC) $(INC)
	$(CC) $(CCFLAGS) $(LIBFLAGS) $(SRC)
	$(CC) -shared *.o -o $(LIB)

clean:
	@-rm -f *.o
	@-rm -f *.gch
	@-rm -f *.so
	@-rm -rf *.dSYM
	@-rm -rf *.gcda
	@-rm -rf *.gcno
