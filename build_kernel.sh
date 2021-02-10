#!/bin/bash


export PLATFORM_VERSION=11
export ANDROID_MAJOR_VERSION=r
export ARCH=arm64
export SEC_BUILD_OPTION_SELINUX_ENFORCE=false

make ARCH=arm64 exynos9610-a51xx_defconfig
make ARCH=arm64 -j4
