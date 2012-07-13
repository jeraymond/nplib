LIB = libnplib.so
OBJ = np_dict.o
INC = np_dict.h np_linkedlist.h
SRC = np_dict.c np_linkedlist.c
CCFLAGS = -std=c99 -pedantic -Wall -W -g -O2 -ansi
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
