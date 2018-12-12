//
// Created by hannes on 30.10.18.
//

#ifndef BlockDeviceHelper_h
#define BlockDeviceHelper_h
#include <stdint.h>
#include <stdlib.h>
#include <type_traits> //Neccessary for is_trivially_copyable
#include <string.h> //Neccessary for memcopy
#define BLOCK_SIZE 512

#include "blockdevice.h"
#include <stdio.h>
#include "constants.h"

class BlockDeviceHelper {
private:
    BlockDevice* blockDevice;

public:

    /**
     * Creates a new IO-Interface for a blockdevice.
     */
    BlockDeviceHelper(BlockDevice* blockdevice) {
        this->blockDevice = blockdevice;
    }

    /**
     * Writes a generic type of data into the blockdevice. Writes to the position block sets.
     * @tparam T The generic type of the data that should be written.
     * @param block The number of the block where the data should be written to.
     * @param data The data that should be written.
     */
    template<class T>
    uint32_t writeDevice(size_t block, T &data, uint32_t blockCount) {
        static_assert(std::is_trivially_copyable<T>::value, "Can't operate on complex types!");

        char *rawData = reinterpret_cast<char *>(&data);

        static char buffer[BLOCK_SIZE];
        size_t currentBlock = block;
        for (; currentBlock < block + blockCount; ++currentBlock) {
            this->blockDevice->write(currentBlock, rawData + ((currentBlock - block) * BLOCK_SIZE));
        }
        memcpy(buffer, rawData + ((currentBlock - block) * BLOCK_SIZE), sizeof(T) % BLOCK_SIZE);
        this->blockDevice->write(currentBlock, buffer);


        return ++currentBlock;
    }

    /**
     * Reads a generic type of data from the blockdevice. The position which should be read from is block.
     * @tparam T The generic type of the data that should be read.
     * @param block The number of the block where the data should be read from.
     * @param data Return parameter,the data that was to be read.
     */
    template<class T>
    void readDevice(size_t block, T &data) {
        static_assert(std::is_trivially_constructible<T>::value, "Can't operate on complex types!");

        char *rawData = reinterpret_cast<char *>(&data);
        static char buffer[BLOCK_SIZE];
        std::size_t blockCount = sizeof(T) / BLOCK_SIZE;
        std::size_t currentBlock = block;
        for (; currentBlock < block + blockCount; ++currentBlock) {
            blockDevice->read(currentBlock, rawData + ((currentBlock - block) * BLOCK_SIZE));
        }
        blockDevice->read(currentBlock, buffer);
        memcpy(rawData + ((currentBlock - block) * BLOCK_SIZE), buffer, sizeof(T) % BLOCK_SIZE);
    }

    /**
     * Writes a generic type of data-array into the blockdevice. Writes to the position block sets.
     * @tparam T The generic type of the data should be written.
     * @tparam N The size of the data array, that should be written.
     * @param block The number of the block where the data should be written to.
     * @param data The data, an array, that should be written.
     */
    template<class T, size_t N>
    void writeDevice(BlockDevice* blockDevice, size_t block, T (&data)[N], uint32_t blockCount) {
        static_assert(std::is_trivially_copyable<T>::value, "Can't operate on complex types!");

        char *rawData = reinterpret_cast<char *>(&data);

        static char buffer[BLOCK_SIZE];
        size_t currentBlock = block;
        for (; currentBlock < block + blockCount; ++currentBlock) {
            blockDevice->write(currentBlock, rawData + ((currentBlock - block) * BLOCK_SIZE));
        }
        memcpy(buffer, rawData + ((currentBlock - block) * BLOCK_SIZE), (sizeof(T) * N) % BLOCK_SIZE);
        blockDevice->write(currentBlock, buffer);
    }

    /**
     * Reads a generic type of data-array from the blockdevice. The position which should be read from is block.
     * @tparam T The generic type of the data should be read.
     * @tparam N The size of the data array, that should be read.
     * @param block The number of the block where the data should be read from.
     * @param data Return parameter, the data, an array, that was to be read.
     */
    template<class T, size_t N>
    void readDevice(std::size_t block, T (&data)[N]) {
        static_assert(std::is_trivially_constructible<T>::value, "Can't operate on complex types!");

        char *rawData = reinterpret_cast<char *>(&data);
        static char buffer[BLOCK_SIZE];
        std::size_t blockCount = (sizeof(T) * N) / BLOCK_SIZE;
        std::size_t currentBlock = block;
        for (; currentBlock < block + blockCount; ++currentBlock) {
            blockDevice->read(currentBlock, rawData + ((currentBlock - block) * BLOCK_SIZE));
        }
        blockDevice->read(currentBlock, buffer);
        memcpy(rawData + ((currentBlock - block) * BLOCK_SIZE), buffer, (sizeof(T) * N) % BLOCK_SIZE);
    }

};

#endif //BlockDeviceHelper_h
