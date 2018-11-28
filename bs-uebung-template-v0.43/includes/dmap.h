#ifndef dmap_h
#define dmap_h

#include <stdio.h>
#include <cstdint>

#define BD_BLOCK_SIZE 512
#define NUMBER_OF_BLOCKS 62500
#define NUMBER_OF_FIELD_ELEMENTS 1954 
/* Es werden vorzeichenlose 32bit Integer verwendet.
 * Der Wert von NUMBER_OF_FIELD_ELEMENTS ergibt sich:
 * NUMBER_OF_BLOCKS / 32 = 1953,125 -> Aufgerundet: 1954  
 */

class DMap {
private:
	uint32_t allocated[NUMBER_OF_FIELD_ELEMENTS];
    
public:
	DMap();
	void setBlockAllocated(int blocknbr);
	bool isBlockAllocated(int blocknbr);
	uint32_t* getDMap();

};

#endif /* dmap_h */
