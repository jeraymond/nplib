LIB = libnplib.so
OBJ = np_dict.o
SRC = np_dict.h np_dict.c \
	np_linkedlist.h np_linkedlist.c
CCFLAGS = -std=c99 -pedantic -Wall -W -g -O2 -ansi
LIBFLAGS = -fpic -c

all: $(LIB)

$(LIB): $(SRC)
	$(CC) $(CCFLAGS) $(LIBFLAGS) $(SRC)
	$(CC) -shared *.o -o $(LIB)

clean:
	@-rm -f *.o
	@-rm -f *.gch
	@-rm -f *.so
	@-rm -f $(TEST_TARGET)
	@-rm -rf *.dSYM
