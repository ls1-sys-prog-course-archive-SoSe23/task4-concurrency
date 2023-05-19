ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

PYTHON3 ?= python3
CFLAGS += -g -w -pthread -fpermissive
#CFLAGS += -O2
HEADERS := ${ROOT_DIR}/../
CFLAGS += -I$(HEADERS)
CPPFLAGS += $(CFLAGS)

PROG1 := ${ROOT_DIR}/test_mutual_exclusion
PROG2 := ${ROOT_DIR}/test_locklinkedlist
PROG3 := ${ROOT_DIR}/test_lockfreelinkedlist
PROG4 := ${ROOT_DIR}/test_lockhashmap
PROG5 := ${ROOT_DIR}/test_lockfreehashmap
PROG6 := ${ROOT_DIR}/test_cleanup_lock
PROG7 := ${ROOT_DIR}/test_cleanup_lockfree

OBJS := ${SRCS:.c=.so}

LIBS = -Wl,-rpath,${ROOT_DIR}/.. -L ${ROOT_DIR}/.. -Wl,-rpath,${ROOT_DIR}/../target/release -L ${ROOT_DIR}/../target/release -Wl,-rpath,${ROOT_DIR}/../target/debug -L ${ROOT_DIR}/../target/debug

LIBS1 = -lspinlock
LIBS2 = -llocklinkedlist
LIBS3 = -llockfreelinkedlist
LIBS4 = -llockhashmap
LIBS5 = -llockfreehashmap

all: $(PROG1) $(PROG2) $(PROG3) $(PROG4) $(PROG5) $(PROG6) $(PROG7)

#check: $(TEST1) $(TEST2) $(TEST3) $(TEST4) $(TEST5)
#	$(PYTHON3) ${ROOT_DIR}/test_mutual_exclusion.py
#	$(PYTHON3) ${ROOT_DIR}/test_locklinkedlist.py
#	$(PYTHON3) ${ROOT_DIR}/test_lockhashmap.py
#	$(PYTHON3) ${ROOT_DIR}/test_lockfreehashmap.py

check: $(PROG1) $(PROG2) $(PROG3) $(PROG4) $(PROG5)
	$(PYTHON3) ${ROOT_DIR}/test_mutual_exclusion.py
	$(PYTHON3) ${ROOT_DIR}/test_locklinkedlist.py
	$(PYTHON3) ${ROOT_DIR}/test_lockfreelinkedlist.py
	$(PYTHON3) ${ROOT_DIR}/test_lockhashmap.py
	$(PYTHON3) ${ROOT_DIR}/test_lockfreehashmap.py

SRCS = \
	${ROOT_DIR}/thread.c \
    #${ROOT_DIR}/hashmap-driver.c \

$(PROG1): ${ROOT_DIR}/test_mutual_exclusion.c
	$(CC) $(CFLAGS) -Og -g -pthread -o $@ $< $(LIBS) $(LIBS1)

$(PROG2): ${ROOT_DIR}/test_locklinkedlist.c
	$(CC) $(CFLAGS) -Og -g -pthread -o $@ $< $(LIBS) $(LIBS1) $(LIBS2)

$(PROG3): ${ROOT_DIR}/test_lockfreelinkedlist.c
	$(CC) $(CFLAGS) -Og -g -pthread -o $@ $< $(LIBS) $(LIBS3)

$(PROG4): $(ROOT_DIR)/test_lockhashmap.c $(SRCS)
	$(CC) $(CFLAGS) -Og -g -pthread -o $@ $< $(SRCS) $(LIBS) $(LIBS1) $(LIBS2) $(LIBS4)

$(PROG5): ${ROOT_DIR}/test_lockfreehashmap.c $(SRCS)
	$(CC) $(CFLAGS) -Og -g -pthread -o $@ $< $(SRCS) $(LIBS) $(LIBS3) $(LIBS5)

$(PROG6): ${ROOT_DIR}/test_cleanup.c
	$(CC) $(CFLAGS) -Og -g -o $@ $< $(LIBS) $(LIBS1) $(LIBS2) $(LIBS4)

$(PROG7): ${ROOT_DIR}/test_cleanup.c
	$(CC) $(CFLAGS) -Og -g -o $@ $< $(LIBS) $(LIBS3) $(LIBS5)

clean:
	$(RM) $(OBJS) $(PROG1) $(PROG2) $(PROG3) $(PROG4) $(PROG5) $(PROG6) $(PROG7)