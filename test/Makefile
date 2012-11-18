UNAME = $(shell sh -c 'uname -s 2>/dev/null || echo not')
TARGET = np-lib-test
INC = np_hashmap_test.h np_treemap_test.h np_linkedlist_test.h np_arraylist_test.h
SRC = np_hashmap_test.c np_treemap_test.c np_linkedlist_test.c np_arraylist_test.c
SRC += np_lib_test.c
CFLAGS += -std=c99 -pedantic -Wall -g -O2 -I ../src
LDFLAGS += -lcunit -lnplib -L ../src
LD_PATH = ../src
ifeq ($(UNAME),Darwin)
	LD_LIB = DYLD_LIBRARY_PATH
else
	LD_LIB = LD_LIBRARY_PATH
endif

# Finding CUnit on FreeBSD
ifeq ($(UNAME),FreeBSD)
	CFLAGS += -I/usr/local/include
	LDFLAGS += -L/usr/local/lib
endif

all: $(TARGET)

$(TARGET): $(SRC) $(INC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	@-rm -f *.o
	@-rm -f *.gch
	@-rm -f *.so
	@-rm -f $(TARGET)
	@-rm -rf *.dSYM
	@-rm -rf *.gcda
	@-rm -rf *.gcno

check: all
	$(LD_LIB)='$(LD_PATH)' ./$(TARGET)