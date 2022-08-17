#!/bin/bash


#export PLATFORM_VERSION=12
#export ANDROID_MAJOR_VERSION=r
#export ARCH=arm64
#export SEC_BUILD_OPTION_SELINUX_ENFORCE=false

if [ ! -f .config ]; then
	make a51-linux11_defconfig
fi
make -j4
