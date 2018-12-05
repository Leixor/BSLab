#ifndef Dmap_h
#define Dmap_h

#include <stdio.h>
#include <cstdint>
#include "constants.h"

/* Es werden vorzeichenlose 32bit Integer verwendet.
 * Der Wert von NUMBER_OF_FIELD_ELEMENTS ergibt sich:
 * NUMBER_OF_BLOCKS / 32 = 1953,125 -> Aufgerundet: 1954  
 */

class DMap {
private:
	uint32_t allocated[NUMBER_OF_ELEMENTS];
    
public:
	DMap();
	void setBlockAllocated(int blocknbr);
	bool isBlockAllocated(int blocknbr);
	uint32_t* getDMap();
};

#endif /* Dmap_h */
