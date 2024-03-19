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

Build the kernel:

``` bash
cd kernel
./build_kernel.sh
```

Please add 'isolcpus=2,3' to the kernel boot parameters. Replace
2 and 3 with the core you want to test the PoC on and the corresponding
sibling.

Reboot into new kernel. Note: you have to disable secure boot.

## Testing FineIBT Bypass PoC (unix_poll)

First, install the kernel module:

``` bash
cd kernel_modules/patch_kernel_module
sudo ./run.sh
```

To test the leakage rate:

``` bash
cd fineibt-bypass
sudo ./run_fast.sh
```

To test the full PoC, including the collision finding phase.
Note that the collision-finding phase can take up-to 5 minutes

``` bash
cd fineibt-bypass
sudo ./run.sh
```

Note: Please re-run the PoC a few times and reboot once. The leakage
rates can differ across boots and runs.

## Testing FineIBT Speculation Windows

First, install the kernel module:

``` bash
cd kernel_modules/ibt_tests_kernel_module
sudo ./run.sh
```

To start the test:
Please select two performance sibling cores. We selected for the i9-13900K
and i9-12900K CPUs core 2 and 3 and for the i7-11800H CPU core 2 and 10. Please
adjust the cores in the file `spec-window-test\targets.h'

The test takes approximately 8 hours. So please run it via a separate session
(e.g., `tmux`).
To run the test (adjust the CPU name):

``` bash
cd spec-window-test
sudo ./run.sh i9-13900K
```

To analyze the results:

``` bash
./analyze_all.sh spec-window-test/results/

# Filter for fine_ibt results:
./analyze_all.sh spec-window-test/results/ fineibt

# Filter for ibt results:
./analyze_all.sh spec-window-test/results/ ibt
```

Our results are included in the folder `spec-window-results`.
As shown in Table 4 of the paper, we used the following configs for the
different CPUs.

- i7-11800H: C1 (2 outer 5 inner)
- i9-12900K: C2 (1 outer 9 inner)
- i9-13900K: C3 (2 outer 8 inner)


