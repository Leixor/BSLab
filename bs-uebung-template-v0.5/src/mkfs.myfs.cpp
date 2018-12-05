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
#include "RootData.h"
#include <iostream>
#include <fstream>
#include <unistd.h>

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

	uint32_t firstBlock = superBlockCount + fatBlockCount + dmapBlockCount + rootDirectoryBlockCount +4;
	printf("%d", firstBlock);
	if (argc == 2) {
		//uint32_t dmapStart = blockDeviceHelper->writeDevice(0, superblock, superBlockCount);
		//uint32_t fatStart = blockDeviceHelper->writeDevice(dmapStart, *dmap->getDMap(), dmapBlockCount);
		//uint32_t rootDirectoryStart = blockDeviceHelper->writeDevice(fatStart, *fat->getFat(), fatBlockCount);
		//blockDeviceHelper->writeDevice(rootDirectoryStart, *rootDirectory->getRootDirectory(), rootDirectoryBlockCount);
	} else if(argc > 2) {
		for (int i = 2; i < argc; i++) {
			char* filename = argv[i];
			int fileDescriptor = open(filename, O_RDONLY);

			if (fileDescriptor == -1) {

			} else {
				char buffer[BLOCK_SIZE];
				RootData rootData =  RootData();
				rootData.name = filename;
				rootData.mode = 4;

				ssize_t fileStream = read(fileDescriptor, buffer, BLOCK_SIZE);

				uint32_t nextBlock = dmap->getNextFreeBlock(firstBlock);
				uint32_t currentBlock;

				if (nextBlock == -1) {
					return -1;
				}


				while(fileStream > 0) {
					blockDeviceHelper->writeDevice(nextBlock, buffer, 0);
					dmap->setBlockAllocated(nextBlock);

					currentBlock = nextBlock;

					nextBlock = dmap->getNextFreeBlock(firstBlock);

					fat->setNextBlock(currentBlock, nextBlock);

					rootData.size += fileStream;
					fileStream = read(fileDescriptor, buffer, BLOCK_SIZE);
				}

				fat->setNextBlock(currentBlock, FAT_EOF);

				rootDirectory->addToRootDirectory(rootData, -1);
			}



			// READ FILE

			// ADD TO ROOT_DIRECTORY

			// GET ROOT DATA ENTRY

			// WRITE BLOCKS
				// ADD EVERYTHING ROOT DATA
				// CHECK IN DMAP
				// ADD TO DMAP
				// ADD TO FAT
		}

		uint32_t dmapStart = blockDeviceHelper->writeDevice(0, superblock, superBlockCount);
		uint32_t fatStart = blockDeviceHelper->writeDevice(dmapStart, *dmap->getDMap(), dmapBlockCount);
		uint32_t rootDirectoryStart = blockDeviceHelper->writeDevice(fatStart, *fat->getFat(), fatBlockCount);
		blockDeviceHelper->writeDevice(rootDirectoryStart, *rootDirectory->getRootDirectory(), rootDirectoryBlockCount);

	}

	return 0;
}
