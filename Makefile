arch ?= i686
qemu ?= i386
target ?= $(arch)-elf
kernel := build/arch/$(arch)/kernel.bin
iso := build/arch/$(arch)/osdev.iso

linker_script := src/arch/$(arch)/linker.ld
grub_cfg := src/arch/$(arch)/grub.cfg
assembly_source_files := $(wildcard src/arch/$(arch)/*.asm)
assembly_object_files := $(patsubst src/arch/$(arch)/%.asm, \
    build/arch/$(arch)/%.o, $(assembly_source_files))

.PHONY: clean kernel iso

clean:
	@rm -r build

kernel: $(kernel)

$(kernel):
	@mkdir -p build/arch/$(arch)/
	@$(target)-as src/arch/$(arch)/boot.asm \
		-o build/arch/$(arch)/boot.o
	@$(target)-gcc \
		-c src/kernel.c \
		-o build/arch/$(arch)/kernel.o \
		-std=gnu99 \
		-ffreestanding \
		-O2 \
		-Wall \
		-Wextra
	@$(target)-gcc \
		-T $(linker_script) \
		-o $(kernel) \
		-ffreestanding \
		-O2 \
		-nostdlib \
		build/arch/$(arch)/boot.o \
		build/arch/$(arch)/kernel.o \
		-lgcc
	@grub-file --is-x86-multiboot $(kernel)

iso: $(iso)

$(iso): $(kernel)
	@mkdir -p build/iso/boot/grub
	@cp $(kernel) build/iso/boot/kernel.bin
	@cp $(grub_cfg) build/iso/boot/grub/grub.cfg
	@grub-mkrescue \
		-o $(iso) \
		-d /usr/lib/grub/i386-pc \
		build/iso

run: $(iso)
	@qemu-system-$(qemu) \
		-nographic \
		-curses \
		-vga std \
		-serial mon:stdio \
		-cdrom $(iso)