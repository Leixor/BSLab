#include "fat.h"

fat::fat(int test)
{
	for (int i = 0; i < BLOCK_NUMBER; i++) {
		this->fatList[i] = EOF;
	}
}

fat::~fat()
{
}

uint32_t fat::setNextBlock(uint32_t currentBlock, uint32_t nextBlock)
{
	this->fatList[currentBlock] = nextBlock;
}

uint32_t fat::getNextBlock(uint32_t currentBlock)
{
	return this->fatList[currentBlock];
}

uint32_t fat::getAllBlocks(uint32_t startBlock)
{
	uint32_t blocks[1] = [startBlock];

	uint32_t block = startBlock;
	while (block != EOF) {
		std::vector<int> blocks
		block = this->getNextBlock(block);
	}
}
