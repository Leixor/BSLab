#include "fat.h"

fat::fat(int test)
{
	for (int i = 0; i < BLOCK_NUMBER; i++) {
		this->fatList[i] = FAT_EOF;
	}
}

fat::~fat()
{
}

void fat::setNextBlock(uint32_t currentBlock, uint32_t nextBlock)
{
	this->fatList[currentBlock] = nextBlock;
}

uint32_t fat::getNextBlock(uint32_t currentBlock)
{
	return this->fatList[currentBlock];
}
