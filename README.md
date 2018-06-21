# OS Development Project

Proof of concept kernel/operating-system.

## Reading

- [OsDev Wiki](https://wiki.osdev.org/)
- [Writing an OS in Rust](https://os.phil-opp.com/first-edition/)
- [Booting from Grub2 to x86 long mode ](http://ringzeroandlower.com/2017/08/08/x86-64-kernel-boot.html)

## References

- [PhoeniX OS](https://git.phoenix.dj/phoenix/phoenix-os/tree/master)
- [Antares Kernel](https://github.com/Such13373rHax0r/ANTARES-KERNEL)
- [Dennix](https://github.com/dennis95/dennix)
- [Aura](https://github.com/neonorb/aura)
- [kOS](https://github.com/kissthink/kos)
- [Baremetal x86_64](https://github.com/winksaville/baremetal-x86_64)

## Development Environment

The entire development envoriment is contained within a docker image, including the cross compilers and emulators.

`sh shell.sh`

## Building and Running

Once inside the development envorinment one can use the helper scripts to build and run project.

`sh clean.sh`

`sh headers.sh`

`sh iso.sh`

`sh qemu.sh`

## Debugging

(gdb) set arch i386:x86-64
(gdb) target remote localhost:1234

## Exit Kernel Emulator

Ctrl A + X

## Development Tasks

- [x] Meaty (folder structure, libc, etc)
- [x] Scrolling Terminal
- [x] Terminal escape codes
- [x] Multiboot2
- [ ] Parse boot info
- [x] x86_64
- [ ] C++
- [ ] Bazel
- [x] Long Mode
- [ ] Paging
- [ ] Interrupts
- [ ] SysCalls
- [ ] User Space
- [ ] uEFI
- [ ] Bootloader error codes -> ascii
- [ ] SSE
