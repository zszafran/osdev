# OS Development Project

Proof of concept kernel/operating-system.

This is a hobbyist project with the goal of building everything from scratch.

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

`sh qemu.sh`

## Debugging

To debug the kernel including bootstrap code use `sh qemu-gdb.sh` which will
start the emulator and wait for a debugger to connect before executing anything.

Unfortunately gdb has an issue when the kernel switches to long mode. A patched
version of gdb has been included in the tools/gdb directory or you can choose to
compiler your own from [here](https://github.com/phil-opp/binutils-gdb#gdb-for-64-bit-rust-operating-systems).

Docker is already forwarding the gdbserver port to the host machine, so after
starting qemu in the container just run gdb on the host machine and connect it
to the remote target:

```shell
(gdb) set arch i386:x86-64
(gdb) target remote localhost:1234
```

## Emulator

Controlling the QEMU emulator once its boted the kernel can be done through
several key combinations.

The most important key combinations are:

- `Ctrl-a + x` which will close the emulator
- `Ctrl-a + c` which will switch to the console

More key combinations [here](https://qemu.weilnetz.de/doc/qemu-doc.html#mux_005fkeys).

Once in the console you can run commands:

```shell
(qemu) info registers
(qemu) info mem
```

More commands [here](https://qemu.weilnetz.de/doc/qemu-doc.html#Commands).

## VSCode Tasks

- **Start Docker** - Starts the container using `shell.sh`
- **Stop Docker** - Stops the container
- **Clean** - Runs `clean.sh` from within the container
- **Qemu** - Runs `qemu.sh` from within the contains
- **Qemu with GDB** - Runs `qemu-gdb.sh` from with the container

## VSCode Debugger

You will need to install the [Native Debug](https://github.com/WebFreak001/code-debug)
extension for the gdb configuration to work.

The default configuration will use the gdb binary located at
`./tools/gdb/bin/x86_64-pc-linux-gnu-gdb` in order to utilize the necessary
patches.

A general workflow should be:

- Start the docker container with `shell.sh` or the VSCode task
- Start Qemu with GDB inside the container with `qemu-gdb.sh` or the VSCode task
- Place a breakpoint from the VSCode debug window
- Select `Attach to EQMU` from the VSCode debug window
- Start stepping through code

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
