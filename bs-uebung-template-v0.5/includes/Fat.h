#pragma once
#define BLOCK_NUMBER 200
#define FAT_EOF -1
#include <stdint.h>
#include <vector>

using namespace std;
class Fat
{
public:
	Fat();
	~Fat();

	uint32_t fatList[BLOCK_NUMBER];

	void setNextBlock(uint32_t currentBlock, uint32_t nextBlock);
	uint32_t getNextBlock(uint32_t currentBlock);
    std::vector<uint32_t> getAllBlocks(uint32_t startBlock);
};
