ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

PYTHON3 ?= python3
CFLAGS += -g -w -pthread -fpermissive
#CFLAGS += -O2
HEADERS := ${ROOT_DIR}/../
CFLAGS += -I$(HEADERS)
CPPFLAGS += $(CFLAGS)

PROG1 := ${ROOT_DIR}/test_mutual_exclusion
PROG2 := ${ROOT_DIR}/test_locklinkedlist
#PROG3 := ${ROOT_DIR}/lock_hashmap
#PROG4 := ${ROOT_DIR}/lockfree_hashmap
#PROG5 := ${ROOT_DIR}/test_cleanup_lock
#PROG6 := ${ROOT_DIR}/test_cleanup_lockfree

OBJS := ${SRCS:.c=.o}

LIBS = -Wl,-rpath,${ROOT_DIR}/.. -L ${ROOT_DIR}/.. -Wl,-rpath,${ROOT_DIR}/../target/release -L ${ROOT_DIR}/../target/release -Wl,-rpath,${ROOT_DIR}/../target/debug -L ${ROOT_DIR}/../target/debug

LIBS1 = $(LIBS) -lspinlock
LIBS2 = $(LIBS) -llocklinkedlist -lspinlock
LIBS3 = $(LIBS) -llockfreehashmap -llockfreelinkedlist

all: $(PROG1) $(PROG2) #$(PROG3) $(PROG4) $(PROG5)

check: $(PROG1) $(PROG2) $(PROG3) $(PROG4) $(PROG5)
	$(PYTHON3) ${ROOT_DIR}/test_mutual_exclusion.py
	$(PYTHON3) ${ROOT_DIR}/test_lockhashmap.py
	$(PYTHON3) ${ROOT_DIR}/test_lockfreehashmap.py

$(PROG1): ${ROOT_DIR}/test_mutual_exclusion.c
	$(CC) $(CFLAGS) -Og -g -pthread -o $@ $< $(LIBS1)

SRCS = \
        ${ROOT_DIR}/thread.c \
		${ROOT_DIR}/test_locklinkedlist.c
        #${ROOT_DIR}/hashmap-driver.c \

$(PROG2): $(SRCS)
	$(CC) $(CFLAGS) -Og -g -pthread -o $@ $(SRCS) $(LIBS1) $(LIBS2)

$(PROG3): $(SRCS)
	$(CC) $(CFLAGS) -Og -g -pthread -o $@ $(SRCS) $(LIBS3)

$(PROG4): ${ROOT_DIR}/test_cleanup.c
	$(CC) $(CFLAGS) -Og -g -o $@ $< $(LIBS2)

$(PROG5): ${ROOT_DIR}/test_cleanup.c
	$(CC) $(CFLAGS) -Og -g -o $@ $< $(LIBS3)

clean:
	$(RM) $(OBJS) $(PROG1) $(PROG2) $(PROG3) $(PROG4) $(PROG5)
