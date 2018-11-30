#include "Fat.h"

Fat::Fat()
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

std::vector<uint32_t> Fat::getAllBlocks(uint32_t startBlock)
{
	std::vector<uint32_t> blocks{startBlock};
	
	uint32_t currentBlock = startBlock;
	
	while(this->getNextBlock(currentBlock) != FAT_EOF)
	{
		blocks.push_back(this->getNextBlock(currentBlock));
		currentBlock = this->getNextBlock(currentBlock);
	}
	
	return blocks;
}
