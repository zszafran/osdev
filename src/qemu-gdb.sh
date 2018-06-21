#!/bin/sh
set -e
. ./iso.sh

qemu-system-$(./target-triplet-to-arch.sh $HOST) \
  -nographic \
	-curses \
	-vga std \
	-serial mon:stdio \
	-cpu max \
	-s -S \
  -cdrom ${OSNAME}.iso
