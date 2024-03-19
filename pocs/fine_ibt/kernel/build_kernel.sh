#!/bin/bash
set -e
# Download source
wget https://github.com/torvalds/linux/archive/refs/tags/v6.6-rc4.tar.gz
tar -xvf v6.6-rc4.tar.gz

# We copy the config
cd linux-6.6-rc4
cp ../config .config

# Apply the patch required for PoC
git apply ../fineibt_poc.patch

make CC=clang-16 olddefconfig

# Build and install
make CC=clang-16 -j `nproc`
make CC=clang-16 modules_install -j `nproc`
make CC=clang-16 install -j `nproc`

echo "Please reboot into the kernel: linux-6.6.0-rc4-fineibt"