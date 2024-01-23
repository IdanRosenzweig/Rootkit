#!/bin/bash

BUILD_DIR=/home/idan/CLionProjects/Rootkit/linux/build

# linux rootkit
ROOTKIT_SOURCE_DIR=/home/idan/CLionProjects/Rootkit/linux
KM_SOURCE_DIR=/home/idan/CLionProjects/Rootkit/linux/kernel_access/kernel_module/
KM_NAME=my_km

# create the build directory
mkdir -p $BUILD_DIR

# cmake the rootkit
cd $BUILD_DIR
cmake -DMODULE_DIR="\"$BUILD_DIR/\"" -DMODULE_NAME="\"$KM_NAME\"" $ROOTKIT_SOURCE_DIR
make -j4

if [ $? -ne 0 ]; then
  echo "Build failed"
  exit
fi

# make the kernel module
cd $KM_SOURCE_DIR
make OUTPUT_DIR=$BUILD_DIR MOD_NAME=$KM_NAME

if [ $? -ne 0 ]; then
  echo "Build failed"
  exit
fi

echo "Build successful"
