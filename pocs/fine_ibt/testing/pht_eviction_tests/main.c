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

#include <sys/mman.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sched.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>

#include "common.h"
#include "targets.h"
#include "flush_and_reload.h"
#include "evict_pht.h"

#define TEST_ITERATIONS 1000


uint8_t * get_phys_map_start() {

    int fd;
    char buf[18];
    uint8_t * address;

    if (access(PATH_PHYS_MAP, F_OK) == 0) {
        fd = open(PATH_PHYS_MAP, O_RDONLY);
        assert(fd);
    } else {
        printf("Error: File %s not found. Please insert the kernel module\n", PATH_PHYS_MAP);
        exit(EXIT_FAILURE);
    }

    assert(read(fd, buf, 18));

    assert(sscanf(buf, "%lx", (uint64_t *) &address) == 1);

    return address;

}

// ----------------------------------------------------------------------------
// MAIN
//
// ----------------------------------------------------------------------------



int main(int argc, char **argv)
{
    struct config cfg = {0};
    uint64_t time_start;


    int seed = time(0);

    printf("Seed: %d\n", seed);
    srand(seed);

    for (size_t i = 0; i < 8; i++)
    {
        cfg.all_pht_cfg[i] =  init_pht_eviction(0);
    }

    cfg.pht_cfg = cfg.all_pht_cfg[0];


    if (access(PATH_CALLER_TRAIN, F_OK) == 0) {
        cfg.fd_caller_train = open(PATH_CALLER_TRAIN, O_WRONLY);
        assert(cfg.fd_caller_train);
    } else {
        printf("Error: File %s not found\n", PATH_CALLER_TRAIN);
        exit(EXIT_FAILURE);
    }

    if (access(PATH_CALLER_TEST, F_OK) == 0) {
        cfg.fd_caller_test = open(PATH_CALLER_TEST, O_WRONLY);
        assert(cfg.fd_caller_test);
    } else {
        printf("Error: File %s not found\n", PATH_CALLER_TEST);
        exit(EXIT_FAILURE);
    }


    // ------------------------------------------------------------------------
    // Allocate a huge page

    cfg.ind_map = allocate_huge_page();
    cfg.ind_map_train = allocate_huge_page();

    cfg.phys_start = get_phys_map_start();
    printf("Direct Physical Map start: %p\n", cfg.phys_start);


    // ------------------------------------------------------------------------
    // Find the kernel address of our huge page

    cfg.ind_map_kern = (uint8_t *)(virt_to_physmap((uint64_t)cfg.ind_map, (uint64_t) cfg.phys_start));
    cfg.ind_map_train_kern = (uint8_t *)(virt_to_physmap((uint64_t)cfg.ind_map_train, (uint64_t) cfg.phys_start));

    while ((uint64_t) cfg.ind_map_kern % HUGE_PAGE_SIZE != 0)
    {
        printf("Invalid huge_page! User: %p Kernel: %p\n", cfg.ind_map, cfg.ind_map_kern);
        sleep(1);
        cfg.ind_map_kern = (uint8_t *)(virt_to_physmap((uint64_t)cfg.ind_map, (uint64_t) cfg.phys_start));
    }
    printf("User huge page addr: %p Kernel huge page addr: %p\n", cfg.ind_map, cfg.ind_map_kern);

    cfg.fr_buf = cfg.ind_map + 0x1000;
    cfg.fr_buf_kern = cfg.ind_map_kern + 0x1000;
    printf("User FR_BUF: %p Kernel FR_BUF: %p\n", cfg.fr_buf, cfg.fr_buf_kern);


    memset(cfg.fr_buf, 0x90, 0x1000);

    // ------------------------------------------------------------------------
    // Setup train ind_map

    *(uint64_t *)(cfg.ind_map_train) = (uint64_t)cfg.ind_map_train_kern;



    // ------------------------------------------------------------------------
    // Dry run for all tests

    printf("----------------------------------------------- ");
    printf(" INCORRECT SID\n");

    printf("%15s%-15s %-15s %-15s %-15s %-15s %-15s %-15s %-15s\n", "",
                "1 LOAD", "2 LOADS", "3 LOADS", "4 LOADS", "5 LOADS", "6 LOADS",
                            "7 LOADS", "8 LOADS"
                            );


    uint64_t counter = 0;
    int pht_id = 0;

    while(1) {

        if (counter++ == 16) {
            printf("%15s%-15s %-15s %-15s %-15s %-15s %-15s %-15s %-15s\n", "",
                        "1 LOAD", "2 LOADS", "3 LOADS", "4 LOADS", "5 LOADS", "6 LOADS",
                                    "7 LOADS", "8 LOADS"
                                    );
            counter = 0;

        }

        cfg.pht_cfg = cfg.all_pht_cfg[pht_id];

        printf("%11s %d ", "PHT", pht_id);
        print_leakage_rate(&cfg, TEST_ITERATIONS);

        for (size_t i = 0; i < 1; i++)
        {
            printf("%12s  ", "");
            print_leakage_rate(&cfg, TEST_ITERATIONS);
        }

        pht_id = (pht_id + 1) % 8;

    }





}
