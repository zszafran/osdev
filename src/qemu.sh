#!/bin/sh
set -e
. ./iso.sh

qemu-system-$(./target-triplet-to-arch.sh $HOST) \
  -nographic \
	-curses \
	-vga std \
	-serial mon:stdio \
  -cdrom myos.iso
