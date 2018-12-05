//
//  rootData.hpp
//  mkfs.myfs
//
//  Created by Mika Auer on 21.11.18.
//  Copyright © 2018 Oliver Waldhorst. All rights reserved.
//

#ifndef RootData_h
#define RootData_h

#include <stdio.h>
#include <stdint.h>
#include <sys/stat.h>

enum Mode {
    READ = 4,
    WRITE = 2,
    EXECUTE = 1
};

struct RootData {
	char* name;
	uint32_t size;
	uint32_t group;
	uint32_t user;
	uint32_t mode;
	time_t atime;
	time_t mtime;
	time_t ctime;
	uint32_t firstBlock;
};

#endif /* rootData_h */
