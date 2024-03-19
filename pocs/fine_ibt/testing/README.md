# Disclosure - FineIBT window tests

This folder contains the IBT and FineIBT transient window tests. The kernel
module `ibt_tests_kernel_module` has to be installed to execute the tests.

Build and install the kernel_module:

``` bash
cd ../kernel/ibt_tests_kernel_module
sudo ./run.sh
```

## paper_window_tests

The folder `paper_window_tests` contains the user program to test
the IBT and FineIBT window with an equalized call path.

During the IBT test the program initiates the kernel module function
`mod_perform_ibt_test` which transiently jumps to a sequence of instructions
that dereference the load chain. This sequence is not preceded by an `endbr`
instruction.

During the FineIBT test the program initiates the kernel module function
`mod_perform_fine_ibt_test` which transiently jumps to
a FineIBT check followed by a sequence of instructions
that dereference the load chain. Prior executing the program selects via
`mod_select_sid` either a correct or fake SID. Before each test run (executing
with a fake SID) the FineIBT branch is trained with two training runs (executing
with a correct SID). There is no need of PHT eviction since the branch history
is equalized after the user programming differentiates between a training and
test run.

The results are included in the enclosed paper.

### Building

``` bash
cd paper_window_tests
make -B
```

### Running

Run IBT test:

``` bash
sudo taskset -c 0 ./main ibt
```

Run FineIBT test:

``` bash
sudo taskset -c 0 ./main fine_ibt
```

Run both the IBT and FineIBT tests 100 times:

``` bash
# first start SMT contention on sibling core
sudo ./run_test.sh with_contention

# first disable sibling core
sudo ./run_test.sh wo_contention
```

Either run the SMT contention on the sibling core or disable it
(see "Workload on sibling core").


## pht_eviction_tests

The folder `pht_eviction_tests` contains the user program to test
the FineIBT window without an equalized call path.

In this test we use for the training and test run call a different call path.
Since the branch predictor can differ between a training and a test run, we
evict the PHT entry prior each iteration. We use a simple (but far from
optimal) eviction strategy by walking 8k branches. The test initializes
several eviction sets and alternates between them.

### Building

``` bash
cd pht_eviction_tests
make -B
```

### Running

Run:

``` bash
sudo taskset -c 0 ./main
```

Either run the SMT contention on the sibling core or disable it
(see "Workload on sibling core").

## Workload on sibling core

Either run the SMT contention on the sibling core or disable it. Please check
the topology (`lscpu --extended`) to retrieve the sibling core of core 0.

Build SMT contention script:

``` bash
cd ../contention
make smt_contention -B
```

Run SMT Contention:

``` bash
taskset -c 1 ./smt_contention 1
```

Disable core:
``` bash
echo 0 | sudo tee /sys/devices/system/cpu/cpu1/online
```
