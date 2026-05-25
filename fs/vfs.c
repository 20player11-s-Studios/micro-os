#include <fs/vfs.h>
#include <kernel/mm.h>
#include <string.h>

struct vfs_node* vfs_root = NULL;

void vfs_init(void) {
    vfs_root = (struct vfs_node*)malloc(sizeof(struct vfs_node));
    strcpy(vfs_root->name, "/");
    vfs_root->flags = FS_DIRECTORY;
    vfs_root->length = 0;
    vfs_root->parent = NULL;
}

int vfs_read(struct vfs_node* node, uint32_t offset, uint32_t size, uint8_t* buffer) {
    if (node->read) return node->read(node, offset, size, buffer);
    return -1;
}

struct vfs_node* vfs_find(const char* path) {
    if (strcmp(path, "/") == 0) return vfs_root;
    // Simple implementation for now
    return NULL;
}
