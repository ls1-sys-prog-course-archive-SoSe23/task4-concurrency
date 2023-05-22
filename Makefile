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
#	cargo build --release
#	mv target/release/libhashmap.so target/release/liblockhashmap.so
#	cargo build --release -p hashmap --no-default-features --features lockfree
#	mv target/release/libhashmap.so target/release/liblockfreehashmap.so

# C/C++ example
all: libspinlock.so liblocklinkedlist.so liblockfreelinkedlist.so liblockhashmap.so liblockfreehashmap.so

libspinlock.so: spinlock.c
	$(CC) $(CFLAGS) -shared -fPIC -ldl -o $@ $<

liblocklinkedlist.so: locklinkedlist.c spinlock.c
	$(CC) $(CFLAGS) -shared -fPIC -ldl -o $@ $< spinlock.c

liblockfreelinkedlist.so: lockfreelinkedlist.c
	$(CC) $(CFLAGS) -shared -fPIC -ldl -o $@ $<

liblockhashmap.so: hashmap.c locklinkedlist.c spinlock.c
	$(CC) $(CFLAGS) -shared -fPIC -ldl -o $@ $< locklinkedlist.c spinlock.c

liblockfreehashmap.so: hashmap.c lockfreelinkedlist.c
	$(CC) $(CFLAGS) -shared -fPIC -ldl -o $@ $< lockfreelinkedlist.c

# Usually there is no need to modify this
check: all
	$(MAKE) -C tests check

clean:
	$(MAKE) -C tests clean
	rm -rf *.so* *.o
