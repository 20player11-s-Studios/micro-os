# MicroOS — Getting Started

MicroOS is a lightweight command-line operating system. Follow these instructions to build and run the system.

## Prerequisites

### Windows (WSL Recommended)
1. **Install WSL**: Open PowerShell as Admin and run `wsl --install`.
2. **Install Tools in WSL (Ubuntu)**:
   ```bash
   sudo apt update
   sudo apt install build-essential qemu-system-x86 grub-pc-bin xorriso mtools
   ```

## Building MicroOS

Inside your WSL terminal, navigate to the project folder and run:

```bash
make clean
make
```

This will create `build/microos.bin`.

## Running MicroOS

### Method 1: Bootable ISO (Recommended)
This is the most reliable method for 64-bit kernels:
```bash
make iso
make run
```
*If you get an error about `grub-mkrescue`, make sure `grub-pc-bin` and `xorriso` are installed.*

### Method 2: Direct Kernel Boot
If your version of QEMU supports it, you can run the binary directly:
```bash
qemu-system-x86_64 -kernel build/microos.bin
```
*Note: If you see "Error loading uncompressed kernel without PVH ELF Note", use Method 1 (ISO) instead.*

## Using the Shell

- Type `help` to see the list of available commands.
- Use `run loop 5` to test the scripting engine.
- Use `exec apps/editor.mos` to test the app loader.
- Use `shutdown` to exit the OS.

## Project Structure

- `/boot`: Assembly entry point and Long Mode transition.
- `/kernel`: Core kernel logic (GDT, IDT, MM, Syscalls).
- `/drivers`: Hardware drivers (E1000, Keyboard, PCI).
- `/shell`: Custom command-line interface.
- `/sdk`: Development kit for .MOS applications.
- `/fs`: Virtual Filesystem (VFS) layer.
