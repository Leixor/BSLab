//
//  Superblock.h
//  mkfs.myfs
//
//  Created by Michael Martel on 26.11.18.
//
#ifndef Superblock_h
#define Superblock_h

#include <stdio.h>
#include <stdint.h>
#include <sys/stat.h>

struct SuperBlock {
    u_int32_t size;
    char name[256];
    u_int32_t dmap_block;
    u_int32_t fat_block;
    u_int32_t rootdir_block;

    // Not sure if needed
    u_int32_t freeBlockCount;
    u_int32_t first_free_block;
    time_t change_time;
};

#endif // Superblock_h
