CFLAGS = -g -O3 -Wno-unused-function -no-pie

all: smt_contention
.PHONY: clean

TARGET = undef

smt_contention: smt_contention.c
	gcc -c snippet.S -o snippet.o
	gcc  -o $@ smt_contention.c snippet.o $(CFLAGS)

clean:
	rm -f smt_contention snippet.o

