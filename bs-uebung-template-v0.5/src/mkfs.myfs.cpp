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

#define numberOfDataBlocks 62500

#define SUPER_BLOCK_START 0
#define DMAP_SIZE
#define FAT_SIZE
#define ROOT_DIRECTORY_SIZE





int main(int argc, char *argv[])
{
	// TODO: Implement file system generation & copying of files here
	BlockDevice blockDevice = BlockDevice();
	SuperBlock* superblock = new SuperBlock();
	DMap* dmap = new DMap();
	Fat* fat = new Fat();
	RootDirectory* rootDirectory = new RootDirectory();

	BlockDeviceHelper* blockDeviceHelper = new BlockDeviceHelper(blockDevice);
	blockDevice.create(argv[1]);

	if (argc > 1) {
		uint32_t dmapStart = blockDeviceHelper->writeDevice(0, superblock);
		uint32_t fatStart = blockDeviceHelper->writeDevice(dmapStart, *dmap->getDMap());
		uint32_t rootDirectoryStart = blockDeviceHelper->writeDevice(fatStart, *fat->getFat());
		blockDeviceHelper->writeDevice(rootDirectoryStart, *rootDirectory->getRootDirectory());
	}



	return 0;
}
