//
//  RootDirectory.hpp
//  mkfs.myfs
//
//  Created by Mika Auer on 21.11.18.
//  Copyright © 2018 Oliver Waldhorst. All rights reserved.
//

#ifndef RootDirectory_h
#define RootDirectory_h
#define DIRECTORY_SIZE 64

#include <stdio.h>
#include "RootData.h"

class RootDirectory
{
	RootData directory[DIRECTORY_SIZE];
    
    RootData *getRootData(const char* path);
    
    int addToRootDirectory;
};


#endif /* RootDirectory_hpp */
