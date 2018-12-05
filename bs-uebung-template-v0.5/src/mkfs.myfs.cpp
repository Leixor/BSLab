//
//  mk.myfs.cpp
//  myfs
//
//  Created by Oliver Waldhorst on 07.09.17.
//  Copyright © 2017 Oliver Waldhorst. All rights reserved.
//

#include "myfs.h"
#include "blockdevice.h"
#include "macros.h"
#include "Fat.h"
#include "Dmap.h"
#include "SuperBlock.h"
#include "RootDirectory.h"
#include "BlockDeviceHelper.h"
#include <iostream>
#include <fstream>

#include <stdio.h>
#include "constants.h"



int main(int argc, char *argv[])
{
	// TODO: Implement file system generation & copying of files here
	BlockDevice blockDevice = BlockDevice();
	SuperBlock* superblock = new SuperBlock();
	DMap* dmap = new DMap();
	Fat* fat = new Fat();
	RootDirectory* rootDirectory = new RootDirectory();

	BlockDeviceHelper* blockDeviceHelper = new BlockDeviceHelper(&blockDevice);
	blockDevice.create(argv[1]);

	uint32_t superBlockCount = sizeof(superblock) / 512;

	uint32_t fatBlockCount = (sizeof(*fat->getFat()) * FAT_SIZE) / 512;

    uint32_t dmapBlockCount = (sizeof(*dmap->getDMap()) * NUMBER_OF_ELEMENTS) / 512;

	uint32_t rootDirectoryBlockCount = (sizeof(rootDirectory->getRootDirectory()) * ROOT_DIRECTORY_SIZE) / 512;

	if (argc > 1) {
		uint32_t dmapStart = blockDeviceHelper->writeDevice(0, superblock, superBlockCount);
		uint32_t fatStart = blockDeviceHelper->writeDevice(dmapStart, *dmap->getDMap(), dmapBlockCount);
		uint32_t rootDirectoryStart = blockDeviceHelper->writeDevice(fatStart, *fat->getFat(), fatBlockCount);
		blockDeviceHelper->writeDevice(rootDirectoryStart, *rootDirectory->getRootDirectory(), rootDirectoryBlockCount);
	} else if(argc > 2) {
		for (int i = 2; i < argc; i++) {
			ofstream file(argv[v], ios::out);
			if(file.is_open()) {

			} else {
				printf("Couldnt open file.");
			}
		}
	}

	return 0;
}
