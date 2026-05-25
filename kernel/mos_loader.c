#include <kernel/tty.h>
#include <fs/vfs.h>
#include <mos.h>
#include <kernel/mm.h>
#include <string.h>

int mos_load_and_run(const char* path) {
    struct vfs_node* node = vfs_find(path);
    if (!node) {
        tty_printf("MOS: App not found: %s\n", path);
        return -1;
    }

    mos_header_t header;
    vfs_read(node, 0, sizeof(mos_header_t), (uint8_t*)&header);

    if (header.magic != MOS_MAGIC) {
        tty_printf("MOS: Invalid magic (Expected 0x%x, got 0x%x)\n", MOS_MAGIC, header.magic);
        return -1;
    }

    tty_printf("MOS: Loading app %s...\n", header.app_name);

    // 1. Allocate memory for the application
    void* app_mem = malloc(node->length);
    if (!app_mem) {
        tty_printf("MOS: Out of memory\n");
        return -1;
    }

    // 2. Load the binary from VFS
    vfs_read(node, 0, node->length, (uint8_t*)app_mem);

    // 3. Setup context and jump to entry point
    void (*entry)() = (void (*)())((uintptr_t)app_mem + header.entry_point);

    tty_printf("MOS: Executing %s at %p\n", header.app_name, entry);

    // In a real OS, we'd switch to user mode here.
    // For now, we call the entry point directly in kernel mode (for simplicity in this task).
    entry();

    return 0;
}
