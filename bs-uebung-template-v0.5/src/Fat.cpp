#include "fat.h"

Fat::fat(int test)
{
	for (int i = 0; i < BLOCK_NUMBER; i++) {
		this->fatList[i] = FAT_EOF;
	}
}

Fat::~Fat()
{
}

void Fat::setNextBlock(uint32_t currentBlock, uint32_t nextBlock)
{
	this->fatList[currentBlock] = nextBlock;
}

uint32_t Fat::getNextBlock(uint32_t currentBlock)
{
	return this->fatList[currentBlock];
}

std::vector<int> Fat::getAllBlocks(uint32_t startBlock)
{
	std::vector<int> blocks{startBlock};
	
	uint32_t currentBlock = startBlock;
	
	while(this->getNextBlock() != FAT_EOF)
	{
		blocks.insert(this->getNextBlock(currentBlock));
		currentBlock = this->getNextBlock(currentBlock);
	}
	
	return blocks;
}
