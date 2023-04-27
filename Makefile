# Set you prefererred CFLAGS/compiler compiler here.
# Our github runner provides gcc-10 by default.
CC ?= cc
CFLAGS ?= -g -Wall
CXX ?= c++
CXXFLAGS ?= -g -Wall
CARGO ?= cargo
RUSTFLAGS ?= -g

# this target should build all executables for all tests
#all:
#	@echo "Please set a concrete build command here"
#	false

.PHONY: clean check

## Rust Example
#all:
#	cargo build

# C/C++ example
all: libspinlock.so liblocklinkedlist.so liblockfreelinkedlist.so libhashmap.so
libspinlock.so: spinlock.c
	$(CC) $(CFLAGS) -shared -fPIC -ldl -o $@ $<

libhashmap.so: hashmap.c
	$(CC) $(CFLAGS) -shared -fPIC -ldl -o $@ $<

liblocklinkedlist.so: locklinkedlist.c
	$(CC) $(CFLAGS) -shared -fPIC -ldl -o $@ $<

liblockfreelinkedlist.so: lockfreelinkedlist.c
	$(CC) $(CFLAGS) -shared -fPIC -ldl -o $@ $<

#liblockfreehashmap.so: lockfreehashmap.c
#	$(CC) $(CFLAGS) -shared -fPIC -ldl -o $@ $<

# Usually there is no need to modify this
check: all
	$(MAKE) -C tests check

clean:
	$(MAKE) -C tests clean
	rm -rf *.so* *.o
