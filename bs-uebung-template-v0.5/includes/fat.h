#pragma once
#define BLOCK_NUMBER
#define EOF -1

class fat
{
public:
	fat(int test);
	~fat();

	uint32_t fatList[BLOCK_NUMBER];

	int setNextBlock(uint32_t currentBlock, uint32_t nextBlock);
	int getNextBlock(uint32_t currentBlock);
};
