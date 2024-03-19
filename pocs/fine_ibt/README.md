# Disclosure - FineIBT Analysis and bypass

This folder contains the IBT and FineIBT window tests and the POC
of the FineIBT bypass using the gadget `unix_poll`.

## Tested environments

The IBT and FineIBT window testing is performed on the following Intel CPUs:

- Intel(R) Core(TM) i7-11800H COU (Rocket Lake)
- Intel(R) Core(TM) i9-12900K CPU (Alder Lake)
- Intel(R) Core(TM) i9-13900K CPU (Raptor Lake)

The PoC is tested on the following Intel CPU:

- Intel(R) Core(TM) i9-13900K CPU (Raptor Lake)

We used Linux kernel v6.6-rc4.

## Creating the test setup

Please download the kernel v6.6-rc4 source code from [here](https://github.com/torvalds/linux/releases/tag/v6.6-rc4).
We used the default Ubuntu config with the options `CONFIG_CFI_CLANG` and `CONFIG_FINEIBT` enabled.
The config used on Raptor Lake (with device specific options enabled) is included in this folder.

### Increase transient window size PoC

The PoC uses a indirect call in syscall 157 as victim. The indirect call
loads a function address from a read-only after init table
(e.g., [security_hook_list](https://elixir.bootlin.com/linux/v6.6-rc4/source/security/commoncap.c#L1443)).
During a attack, the attacker can evict this function table from the cache to
increase the transient window size. We simulate this in the PoC by
flushing the table before the indirect call in the kernel code.

The patch available in this folder should be applied
before compiling the kernel if the PoC wants to be tested.

### Step-by-step

``` bash
wget https://github.com/torvalds/linux/archive/refs/tags/v6.6-rc4.tar.gz
tar -xvf v6.6-rc4.tar.gz
cd linux-6.6-rc4

cp ../config .config
# Only required for PoC:
git apply ../fineibt_poc.patch

make CC=clang-16 bindeb-pkg -j 32
# Next: install kernel and reboot
```
