DEFAULT_HOST!=../default-host.sh
HOST?=DEFAULT_HOST
HOSTARCH!=../target-triplet-to-arch.sh $(HOST)

CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra -fstack-protector-all
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Iinclude
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lk -lgcc

ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)

KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
kernel/ansi.o \
kernel/ctor.o \
kernel/tty.o \
kernel/log.o \
kernel/kernel.o \
boot/info.o \

OBJS=\
$(KERNEL_OBJS) \

LINK_LIST=\
$(LDFLAGS) \
$(KERNEL_OBJS) \
$(LIBS) \

.PHONY: all clean install install-headers install-kernel
.SUFFIXES: .o .c .S

all: kernel.bin

kernel.bin: $(OBJS) linker.gen.ld
	@echo -e "\n\e[33mLinking everything into $@...\e[0m"
	$(CC) -T linker.gen.ld -o $@ $(CFLAGS) $(LINK_LIST)
	grub-file --is-x86-multiboot2 kernel.bin

linker.gen.ld: $(OBJS) linker.ld
	@echo -e "\n\e[33mGenerating link script $@...\e[0m"
	$(CC) -P -D__ASM__ -E -x c linker.ld | grep -v '^#' > $@

.c.o:
	@echo -e "\n\e[33mCompiling $<\e[0m"
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

.S.o:
	@echo -e "\n\e[33mAssembling $<\e[0m"
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)
	@#$(AS) -MD $(@:.o=.d) -o $@ -g --32 $<

clean:
	@rm -f kernel.bin
	@rm -f linker.gen.ld
	@rm -f $(OBJS) *.o */*.o */*/*.o
	@rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-kernel

install-headers:
	@mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-kernel: kernel.bin
	@mkdir -p $(DESTDIR)$(BOOTDIR)
	cp kernel.bin $(DESTDIR)$(BOOTDIR)

-include $(OBJS:.o=.d)
