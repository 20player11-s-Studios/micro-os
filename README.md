# MicroOS — Getting Started

MicroOS is a lightweight command-line operating system. Follow these instructions to build and run the system.

## Prerequisites

To build and run MicroOS, you will need the following tools installed on your system:

- **GCC**: Cross-compiler for x86_64 (or a standard gcc with -m64 support)
- **GNU Assembler (as)**: For the bootloader entry.
- **GNU Binutils (ld)**: For linking the kernel.
- **Make**: To automate the build process.
- **QEMU**: To emulate the hardware and run the OS.

## Building MicroOS

To compile the kernel and applications, simply run:

```bash
make
```

This will create a `build/` directory containing the compiled object files and the final kernel binary: `build/microos.bin`.

## Running MicroOS

### 1. Using QEMU (Easiest)

You can run the kernel directly using QEMU's built-in multiboot loader:

```bash
qemu-system-x86_64 -kernel build/microos.bin
```

### 2. Creating a Bootable ISO

If you have `grub-mkrescue` and `xorriso` installed, you can create a bootable ISO image:

```bash
mkdir -p build/iso/boot/grub
cp build/microos.bin build/iso/boot/
cat << EOF > build/iso/boot/grub/grub.cfg
set timeout=0
set default=0
menuentry "MicroOS" {
    multiboot2 /boot/microos.bin
    boot
}
EOF
grub-mkrescue -o microos.iso build/iso
```

Then run the ISO:

```bash
qemu-system-x86_64 -cdrom microos.iso
```

## Using the Shell

Once MicroOS boots, you will be greeted by the shell.
- Type `help` to see the list of available commands.
- Use `ls` to view the directory structure.
- Use `run loop 5` to test the scripting engine.
- Use `exec apps/editor.mos` (once compiled) to test the .MOS application loader.
- Use `ping 8.8.8.8` to test the network stack simulation.

## Project Structure

- `/boot`: Assembly entry point and Long Mode transition.
- `/kernel`: Core kernel logic (GDT, IDT, MM, Syscalls).
- `/drivers`: Hardware drivers (E1000, Keyboard, PCI).
- `/shell`: Custom command-line interface.
- `/sdk`: Development kit for .MOS applications.
- `/fs`: Virtual Filesystem (VFS) layer.
