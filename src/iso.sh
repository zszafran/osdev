#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/kernel.bin isodir/boot/kernel.bin
cat > isodir/boot/grub/grub.cfg << EOF
set timeout=0
set default=0
menuentry "${OSNAME}" {
	multiboot2 /boot/kernel.bin
  boot
}
EOF
grub-mkrescue \
  -d /usr/lib/grub/i386-pc \
  -o ${OSNAME}.iso isodir
