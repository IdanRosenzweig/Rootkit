#!/bin/bash

BUILD_DIR=/home/idan/CLionProjects/Rootkit/linux/build

# linux rootkit
ROOTKIT_SOURCE_DIR=/home/idan/CLionProjects/Rootkit/linux
KM_SOURCE_DIR=/home/idan/CLionProjects/Rootkit/linux/kernel_access/kernel_module/

# create the build directory
mkdir -p $BUILD_DIR

# cmake the rootkit
cd $BUILD_DIR
cmake -DMODULE_DIR="\"$(BUILD_DIR)/\"" -DMODULE_NAME="\"my_module\"" $ROOTKIT_SOURCE_DIR
make -j4

# make the kernel module
cd $KM_SOURCE_DIR
make OUTPUT_DIR=$BUILD_DIR

if [ $? -eq 0 ]; then
    echo "Build successful"
    # now there are 2 compiled files in the build directory: Rootkit and my_module.ko
else
    echo "Build failed"
fi
