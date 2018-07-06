# OS Development Project

Proof of concept kernel/operating-system.

This is a hobbyist project with the goal of building everything from scratch.

## Reading

- [OsDev Wiki](https://wiki.osdev.org/)
- [Writing an OS in Rust](https://os.phil-opp.com/first-edition/)
- [Booting from Grub2 to x86 long mode ](http://ringzeroandlower.com/2017/08/08/x86-64-kernel-boot.html)
- [Inline Assembly/Examples](https://wiki.osdev.org/Inline_Assembly/Examples)

## References

- [PhoeniX OS](https://git.phoenix.dj/phoenix/phoenix-os/tree/master)
- [Antares Kernel](https://github.com/Such13373rHax0r/ANTARES-KERNEL)
- [Dennix](https://github.com/dennis95/dennix)
- [Aura](https://github.com/neonorb/aura)
- [kOS](https://github.com/kissthink/kos)
- [Baremetal x86_64](https://github.com/winksaville/baremetal-x86_64)
- [Klosy Legacy](https://github.com/kodo-pp/klosy-legacy)

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

- [ ] Phase I - Basics
  - [x] [Setting up a Cross-Toolchain](https://wiki.osdev.org/GCC_Cross_Compiler)
  - [x] [Creating a Hello World kernel](https://wiki.osdev.org/Bare_Bones)
  - [x] [Setting up a Project](https://wiki.osdev.org/Meaty_Skeleton)
    - [x] i386
    - [x] [x86_64 - Long Mode](https://wiki.osdev.org/Long_Mode)
  - [x] [Calling Global Constructors](https://wiki.osdev.org/Calling_Global_Constructors)
  - [x] [Terminal Support](https://wiki.osdev.org/index.php?title=Printf&action=edit&redlink=1)
  - [x] [Stack Smash Protector](https://wiki.osdev.org/Stack_Smashing_Protector)
  - [x] [Multiboot](https://wiki.osdev.org/Multiboot)
  - [x] [Global Descriptor Table](https://wiki.osdev.org/Global_Descriptor_Table)
  - [ ] [Memory Management](https://wiki.osdev.org/Memory_Management)
    - [x] [Page Tables](https://wiki.osdev.org/Setting_Up_Paging)
    - [ ] [Higher Half](https://wiki.osdev.org/Higher_Half_x86_Bare_Bones)
    - [ ] [Page Frame Allocation](https://wiki.osdev.org/Page_Frame_Allocation)
  - [ ] [Interrupts](https://wiki.osdev.org/Interrupts)
  - [ ] [Multithreaded Kernel](https://wiki.osdev.org/index.php?title=Multithreaded_Kernel&action=edit&redlink=1)
  - [ ] [Keyboard](https://wiki.osdev.org/Keyboard)
  - [ ] [Internal Kernel Debugger](https://wiki.osdev.org/index.php?title=Internal_Kernel_Debugger&action=edit&redlink=1)
  - [ ] [Filesystem Support](https://wiki.osdev.org/Filesystem)
    - [ ] [Initialization Ramdisk](https://wiki.osdev.org/Initrd)
- [ ] Phase II - User-Space
  - [ ] [User-Space](https://wiki.osdev.org/index.php?title=User-Space&action=edit&redlink=1)
  - [ ] [Program Loading](https://wiki.osdev.org/index.php?title=Program_Loading&action=edit&redlink=1)
  - [ ] [System Calls](https://wiki.osdev.org/System_Calls)
  - [ ] [OS Specific Toolchain](https://wiki.osdev.org/OS_Specific_Toolchain)
  - [ ] [Creating a C Library](https://wiki.osdev.org/Creating_a_C_Library)
  - [ ] [Fork and Execute](https://wiki.osdev.org/index.php?title=Fork&action=edit&redlink=1)
  - [ ] [Shell](https://wiki.osdev.org/Shell)
- [ ] Phase III - Extending your Operating System
  - [ ] [Time](https://wiki.osdev.org/Time)
  - [ ] [Threads](https://wiki.osdev.org/Thread)
  - [ ] [Thread Local Storage](https://wiki.osdev.org/Thread_Local_Storage)
  - [ ] [Symmetric Multiprocessing](https://wiki.osdev.org/SMP)
  - [ ] [Secondary Storage](https://wiki.osdev.org/index.php?title=Secondary&action=edit&redlink=1)
  - [ ] [Real Filesystems](https://wiki.osdev.org/File_Systems)
  - [ ] [Graphics](https://wiki.osdev.org/How_do_I_set_a_graphics_mode)
  - [ ] [User Interface](https://wiki.osdev.org/User_Interface)
    - [ ] [Compositing](https://wiki.osdev.org/Compositing)
  - [ ] [Networking](https://wiki.osdev.org/Networking)
  - [ ] [Sound](https://wiki.osdev.org/Sound)
  - [ ] [Universal Serial Bus](https://wiki.osdev.org/USB)
- [ ] Phase IV - Bootstrapping
  - [ ] [Porting Software](https://wiki.osdev.org/Cross-Porting_Software)
  - [ ] [Porting GCC](https://wiki.osdev.org/Porting_GCC_to_your_OS)
  - [ ] Compiling your OS under your OS
  - [ ] Fully Self-hosting
