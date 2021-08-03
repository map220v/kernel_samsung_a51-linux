# Linux Kernel for Samsung Galaxy A51
### Installation
1. Create /data/linux.img and format it to any supported by kernel filesystem.
2. Mount /data/linux.img and extract arm64 or armhf linux rootfs and setup it (Arch Linux or other cli linux distro setup knowledge recommended).
3. Flash Linux11.img to recovery partition and reboot to recovery to test installation.

/vendor folder with contents from vendor partition is recommended (to start wifi)

### Dual Boot info
Starting from Android 11 Samsung removed on Exynos ability to enter recovery using power + up vol without usb data connection (PC or USB headphones).
On Android 11 Exynos you can reboot to recovery using Magisk or other programs that can reboot to recovery.
Also "reboot recovery" command in Android should work too.

To reboot back to android from emergency shell use "reboot -f". In Linux every reboot method should work.

If Hard Reset or Kernel Panic happened in Linux, phone boots to Linux instead of Android.

### TODO
o Add more Screen Resolutions
