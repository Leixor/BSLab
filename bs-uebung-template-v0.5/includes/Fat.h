#pragma once
#define BLOCK_NUMBER 200
#define FAT_EOF -1
#include <stdint.h>
#include <vector>
#include <stdio.h>
#include "constants.h"
using namespace std;
class Fat
{
public:
	Fat();
	~Fat();

	uint32_t fatList[FAT_SIZE];

	void setNextBlock(uint32_t currentBlock, uint32_t nextBlock);
	uint32_t getNextBlock(uint32_t currentBlock);
    std::vector<uint32_t> getAllBlocks(uint32_t startBlock);
    uint32_t* getFat();
};
