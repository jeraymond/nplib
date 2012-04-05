UNAME = $(shell sh -c 'uname -s 2>/dev/null || echo not')
TARGET = np-lib-test
SRC = np_lib_test.c \
	np_dict_test.h np_dict_test.c \
	np_linkedlist_test.h np_linkedlist_test.c
CCFLAGS = -std=c99 -pedantic -Wall -g -O2 -ansi -lcunit -lnplib -I ../src \
		-L ../src
LD_PATH = ../src
ifeq ($(UNAME),Darwin)
	LD_LIB = DYLD_LIBRARY_PATH
else
	LD_LIB = LD_LIBRARY_PATH
endif

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CCFLAGS) $(SRC) -o $(TARGET)

clean:
	@-rm -f *.o
	@-rm -f *.gch
	@-rm -f *.so
	@-rm -f $(TARGET)
	@-rm -rf *.dSYM

check: all
	$(LD_LIB)='$(LD_PATH)' ./$(TARGET)