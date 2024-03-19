CFLAGS = -g -O3 -Wno-unused-function

ARCH = undef
OS = undef

all: main
.PHONY: clean

main: main.c
	gcc -c snippet.S -o snippet.o
	gcc -lm  -o $@ main.c flush_and_reload.c colliding_bhb.c ../lib/kaslr_prefetch/kaslr_prefetch.c ../lib/l2_eviction/evict_sys_table_l2.c snippet.o $(CFLAGS) -D$(ARCH) -D$(OS)

clean:
	rm -f main snippet.o

