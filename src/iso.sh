#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/myos.kernel isodir/boot/myos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
set timeout=0
set default=0
menuentry "myos" {
	multiboot2 /boot/myos.kernel
  boot
}
EOF
grub-mkrescue \
  -d /usr/lib/grub/i386-pc \
  -o myos.iso isodir
