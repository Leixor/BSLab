#pragma once
#define BLOCK_NUMBER 200
#define EOF -1
#include <stdint.h>

class fat
{
public:
	fat(int test);
	~fat();

	uint32_t fatList[BLOCK_NUMBER];

	void setNextBlock(uint32_t currentBlock, uint32_t nextBlock);
	uint32_t getNextBlock(uint32_t currentBlock);
};
