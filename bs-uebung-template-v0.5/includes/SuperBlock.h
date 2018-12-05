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
    u_int32_t dmapBlock;
    u_int32_t fatBlock;
    u_int32_t rootdirBlock;
    u_int32_t freeBlockCount;
    u_int32_t firstFreeBlock;
    time_t changeTime;
};

#endif // Superblock_h
