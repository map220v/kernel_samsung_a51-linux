#!/bin/bash


export PLATFORM_VERSION=11
export ANDROID_MAJOR_VERSION=r
export ARCH=arm64
export SEC_BUILD_OPTION_SELINUX_ENFORCE=false

if [ ! -f .config ]; then
	make ARCH=arm64 a51-linux11_defconfig
fi
make ARCH=arm64 -j4
