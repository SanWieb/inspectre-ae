/*
 * Friday, October 27th 2023
 *
 * Sander Wiebing - s.j.wiebing@vu.nl
 * Alvise de Faveri Tron - a.de.faveri.tron@vu.nl
 * Herbert Bos - herbertb@cs.vu.nl
 * Cristiano Giuffrida - giuffrida@cs.vu.nl
 *
 * Vrije Universiteit Amsterdam - Amsterdam, The Netherlands
 *
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

extern void single_outer();
extern void double_outer();

int main(int argc, char **argv)
{

    assert(argc == 2);
    int option = atoi(argv[1]);
    printf("Lets create some SMT contention!\n");

    switch (option)
    {
    case 0:
        printf("Option 0\n");
        single_outer();
        break;
    case 1:
        printf("Option 1\n");
        double_outer();
        break;
    default:
        break;
    }
}
