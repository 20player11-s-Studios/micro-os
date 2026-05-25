# MicroOS Makefile

# Compilation tools
CC = gcc
AS = as
LD = ld
OBJCOPY = objcopy

# Compilation flags
CFLAGS = -m64 -ffreestanding -O2 -Wall -Wextra -nostdlib -fno-stack-protector -fno-pie -Iinclude
ASFLAGS = --64
LDFLAGS = -n -T kernel/linker.ld

# Directories
KERNEL_DIR = kernel
BOOT_DIR = boot
DRIVERS_DIR = drivers
FS_DIR = fs
SHELL_DIR = shell
LIB_DIR = lib
BUILD_DIR = build

# Source files
KERNEL_SOURCES = $(wildcard $(KERNEL_DIR)/*.c)
DRIVER_SOURCES = $(wildcard $(DRIVERS_DIR)/*.c)
FS_SOURCES = $(wildcard $(FS_DIR)/*.c)
SHELL_SOURCES = $(wildcard $(SHELL_DIR)/*.c)
LIB_SOURCES = $(wildcard $(LIB_DIR)/*.c)
BOOT_ASM = $(BOOT_DIR)/boot.s

# Object files
KERNEL_OBJS = $(KERNEL_SOURCES:%.c=$(BUILD_DIR)/%.o)
DRIVER_OBJS = $(DRIVER_SOURCES:%.c=$(BUILD_DIR)/%.o)
FS_OBJS = $(FS_SOURCES:%.c=$(BUILD_DIR)/%.o)
SHELL_OBJS = $(SHELL_SOURCES:%.c=$(BUILD_DIR)/%.o)
LIB_OBJS = $(LIB_SOURCES:%.c=$(BUILD_DIR)/%.o)
BOOT_OBJ = $(BUILD_DIR)/boot/boot.o

ALL_OBJS = $(BOOT_OBJ) $(KERNEL_OBJS) $(DRIVER_OBJS) $(FS_OBJS) $(SHELL_OBJS) $(LIB_OBJS)

# Targets
.PHONY: all clean kernel iso

all: kernel

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

kernel: $(ALL_OBJS)
	@mkdir -p $(BUILD_DIR)
	$(LD) $(LDFLAGS) -o $(BUILD_DIR)/microos.bin $(ALL_OBJS)

clean:
	rm -rf $(BUILD_DIR)
