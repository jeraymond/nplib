all:
	cd src && $(MAKE)

clean:
	cd src && $(MAKE) clean
	cd test && $(MAKE) clean

check: all
	cd test && $(MAKE) check

