# OS Development Project

Proof of concept kernel/operating-system.

## Reading

- [OsDev Wiki](https://wiki.osdev.org/)
- [Writing an OS in Rust](https://os.phil-opp.com/first-edition/)

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

TODO: figure this out

## Exit Kernel Emulator

Ctrl A + X

## Development Tasks

- [x] Meaty (folder structure, libc, etc)
- [x] Scrolling Terminal
- [x] Terminal escape codes
- [x] Multiboot2
- [ ] Parse boot info
- [ ] x86_64
- [ ] C++
- [ ] Bazel
- [ ] Long Mode
- [ ] Paging
- [ ] Interrupts
- [ ] SysCalls
- [ ] User Space
