Linux11.img mounts file systems and starts /sbin/init from sda33(Partition created by resizing sda32(userdata))
/vendor folder with contents from vendor partition is recommended(to start wifi)

After xorg start might be necessary to use "echo 0 > /sys/class/graphics/fb0/rotate" to start display update
