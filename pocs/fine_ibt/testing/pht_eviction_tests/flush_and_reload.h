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

#ifndef _FLUSH_AND_RELOAD_H_
#define _FLUSH_AND_RELOAD_H_

#include <stdint.h>
#include "evict_pht.h"

struct config {
    int fd_caller_train;
    int fd_caller_test;

    uint8_t * fr_buf;
    uint8_t * fr_buf_kern;
    uint8_t * reload_addr;
    uint8_t * ind_map;
    uint8_t * ind_map_kern;


    uint8_t * ind_map_train;
    uint8_t * ind_map_train_kern;
    uint8_t * phys_start;


    uint8_t * gadget_arg;

    pht_config * pht_cfg;
    pht_config * all_pht_cfg[8];

};

void set_load_chain_simple_touch(struct config * cfg, int number_of_loads);
uint64_t do_flush_and_reload(struct config * cfg, uint64_t iterations, uint8_t ret_on_hit);

void print_leakage_rate(struct config * cfg, uint64_t iterations);



#endif //_FLUSH_AND_RELOAD_H_
