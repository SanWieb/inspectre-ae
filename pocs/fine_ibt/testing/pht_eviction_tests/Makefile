CFLAGS = -g -O3 -Wno-unused-function -lrt -lm -no-pie # -fsanitize=address

ARCH = undef
OS = undef

all: main
.PHONY: clean

main: main.c
	gcc -lm -o $@ main.c flush_and_reload.c evict_pht.c $(CFLAGS) -D$(ARCH) -D$(OS)

clean:
	rm -f main snippet.o

