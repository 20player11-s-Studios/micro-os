#ifndef MOS_H
#define MOS_H

#include <stdint.h>

#define MOS_MAGIC 0x4D4F5321 // "MOS!"

typedef struct {
    uint32_t magic;
    uint32_t version;
    uint32_t entry_point;
    uint32_t data_offset;
    uint32_t data_size;
    char app_name[32];
} mos_header_t;

#endif
