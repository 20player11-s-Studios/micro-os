#ifndef VFS_H
#define VFS_H

#include <stdint.h>
#include <stddef.h>

#define FS_FILE 0x01
#define FS_DIRECTORY 0x02

struct vfs_node {
    char name[128];
    uint32_t flags;
    uint32_t length;
    struct vfs_node* parent;
    void* internal_data;

    int (*read)(struct vfs_node*, uint32_t, uint32_t, uint8_t*);
    int (*write)(struct vfs_node*, uint32_t, uint32_t, uint8_t*);
    struct vfs_node* (*finddir)(struct vfs_node*, const char* name);
};

extern struct vfs_node* vfs_root;

void vfs_init(void);
int vfs_read(struct vfs_node* node, uint32_t offset, uint32_t size, uint8_t* buffer);
struct vfs_node* vfs_find(const char* path);

#endif
