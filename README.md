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

### Patches
Framebuffer fix can be found in this commits:
- https://github.com/map220v/a51nsxx_linux/commit/8f88827bf29b4508ed2ea67110de93776a044e74 - fix fb refreshing
- https://github.com/map220v/a51nsxx_linux/commit/83656dabd2b5db98c04c5b02a2eca7b78152bc18 - fix fb colors
- https://github.com/map220v/a51nsxx_linux/commit/974f3e70d07021a9d7b42f08720b0b425003745f - disable framebuffer unmapping (ignore memset comment)
- https://github.com/map220v/a51nsxx_linux/commit/ebfe69da8c0e0c4fcf8fc22970f9e38280d5224f - fix fbpan not refreshing screen (decon_dsi.c file) (fbpan refresh only used to unblank screen when turning it on)
